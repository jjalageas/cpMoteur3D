#include <Image3d.hpp>
#include <ImageMask2d.h>
#include <Information.h>
#include <InterfaceTranscriber.h>
#include <Examen.h>

#include <ImageViewer.h>
#include <SliceViewer.h>

#include <ParserNMI3D.h>
#include <ParserMi3DBinary.h>
#include <ParserDicom.h>

#include <GaussianFilter2d.h>
#include <FilterWindow.h>
#include <FilterWindowTester.h>
#include <FilterDialog.h>
#include <FilterController.h>

#include <LoginFrame.h>

#include <cstdlib>
#include <stdio.h>
#include <signal.h>

#include <QWidget>

using namespace std;

static ImageViewer* imageViewer = NULL;
static SliceViewer* viewer = NULL;
static LoginFrame* login = NULL;

void
usage(char* name)
{
    cout << "usage : " << name << " : " << "path_to_a_dicom_directory -options1 -option2..." << endl << endl;
    cout << "-h : print help" << endl;
    cout << "-gui : gui test" << endl;
    cout << "-gaussian : filter gui test" << endl;
    cout << "-sbmi path.bmi3d : export to a bmi3d file" << endl;
    //cout << "-obmi path.nmi3d : open a bmi3d file" << endl;
    cout << "-snmi path.nmi3d : export to a nmi3d file" << endl;
    cout << "-onmi path.nmi3d : open a nmi3d file" << endl;
    cout << "-v : verbose test of images" << endl;
}

void
testExamen(Examen& exam)
{
    // Print information
    Information *infos = exam.getParams().getContentInformations();
    for (int i=0; i<infos->getSize(); ++i) {
        cout << "title : " << infos->getTitle(i) << ", value : " << infos->getDescription(i) << endl;
    }

    cout << "Examen : ";
    cout << "Width : " << exam.getImageRef().getWidth()
         << ", height : " << exam.getImageRef().getHeight() <<
            ", depth : " << exam.getImageRef().getDepth() << endl;
}

void
testGui(Examen* exam)
{
    viewer = new SliceViewer();

    viewer->setExamen(exam);
    viewer->show();

    imageViewer = new ImageViewer();
    Image<float>* slice = exam->getImageRef().getSlice(0, CORONAL);
    Image<int>* img2 = InterfaceTranscriber::FromImage(slice);
    cout << "nb : " << img2->getWidth() * img2->getHeight() << endl;
    imageViewer->setImage(img2);
    imageViewer->show();
    delete slice;
    delete img2;
}

void
testFilterWindow(Examen *exam)
{
    Filter2D *filter = new GaussianFilter2D();
    cout << "gaussian nbArguments : " << filter->getNbArguments() << endl;
    FilterWindow *win = new FilterWindow(*filter, FilterWindow::OK_CANCEL);
    win->setWindowTitle(QString::fromStdString(filter->getName()));

    new FilterWindowTester(win, exam);
    win->show();
}

void
testImages(Examen& exam)
{
    cout << "Slice : ";
    Image<float>* img = exam.getImageRef().getSlice(0, CORONAL);
    cout << "Width : " << img->getWidth() << ", height : " << img->getHeight() << endl;
    cout << "Max : " << img->getMax() << ", min : " << img->getMin() << endl;

    exam.getImageRef().setModifiedSrc();
    cout << "Global min : " << exam.getImageRef().getMin() << endl;
    cout << "Global max : " << exam.getImageRef().getMax() << endl;
}

void
testParserNmi3D(Examen& exam, string filename)
{
    ParserNMi3D parser_nmi3d;

    // Save Examen
    MiList<bool> options;
    options.add(true);  // image
    options.add(true);  // mask
    options.add(false); // skeleton
    options.add(true); // informations
    parser_nmi3d.saveFile(filename, &exam, options);

    // Load Examen
    int errors;
    Examen* res = parser_nmi3d.loadFile(filename);
    eassert(res != NULL);
    // check image
    if (options.get(0)) {
        Volume* img1 = exam.getImage();
        Volume* img2 = res->getImage();
        eassert(img1->getWidth()  == img2->getWidth());
        eassert(img1->getHeight() == img2->getHeight());
        eassert(img1->getDepth()  == img2->getDepth());
        errors = 0;
        for (int i=0; i < img1->getGlobalSize(); ++i) {
            if (img1->getData()[i] != img2->getData()[i]) {
                errors++;
            }
        }
        eassert(errors == 0);
    }
    // check mask
    if (options.get(1)) {
        Mask3d* mask1 = exam.getMask();
        Mask3d* mask2 = res->getMask();
        eassert(mask1->getWidth()  == mask2->getWidth());
        eassert(mask1->getHeight() == mask2->getHeight());
        eassert(mask1->getDepth()  == mask2->getDepth());
        errors = 0;
        for (int i=0; i < mask1->getGlobalSize(); ++i) {
            if (mask1->getData()[i] != mask2->getData()[i]) {
                errors++;
            }
        }
        eassert(errors == 0);
    }
    // check parameters
    if (options.get(3)) {
        ExamenParams& e1 = exam.getParams();
        ExamenParams& e2 = res->getParams();
        eassert(e1.width == e2.width);
        eassert(e1.height == e2.height);
        eassert(e1.depth == e2.depth);
        eassert(e1.resolutionX == e2.resolutionX);
        eassert(e1.resolutionY == e2.resolutionY);
        eassert(e1.resolutionZ == e2.resolutionZ);
        eassert(e1.getGrayTranslationFunction().getSlope() == e2.getGrayTranslationFunction().getSlope());
        eassert(e1.getGrayTranslationFunction().getIntercept() == e2.getGrayTranslationFunction().getIntercept());
        // check informations
        Information* infos1 = e1.getContentInformations();
        Information* infos2 = e2.getContentInformations();
        eassert(infos1->getSize() == infos2->getSize());
        errors = 0;
        for (int i=0; i < infos1->getSize(); ++i) {
            if ((infos1->getTitle(i).compare(infos2->getTitle(i))) != 0) {
                errors++;
            }
            if ((infos1->getDescription(i).compare(infos2->getDescription(i))) != 0) {
                errors++;
            }
        }
        eassert(errors == 0);
    }
}

void testLogin()
{
    login = new LoginFrame();
    login->show();
}

int
main(int argc, char* argv[])
{
    QApplication* app = new QApplication(argc, argv);
    if (argc <= 1) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    // Load Dicom
    ParserDicom parser_dicom;
    string filepath = argv[1];
    Examen* exam = parser_dicom.loadFile(filepath);
    eassert(exam != NULL);

    bool run_main_qt_loop = false;
    int readen_args = 1;
    while (++readen_args < argc) {
        if (strcmp(argv[readen_args], "-h") == 0) {
            usage(argv[0]);
            return EXIT_SUCCESS;
        }

        if (strcmp(argv[readen_args], "-v") == 0) {
            testExamen(*exam);
            testImages(*exam);
            continue;
        }

        if (strcmp(argv[readen_args], "-tnmi") == 0) {
            if (++readen_args >= argc) {
                usage(argv[0]);
                return EXIT_FAILURE;
            }
            testParserNmi3D(*exam, argv[readen_args]);
            continue;
        }

        if (strcmp(argv[readen_args], "-gui") == 0) {
            testGui(exam);
            run_main_qt_loop = true;
            continue;
        }
        if (strcmp(argv[readen_args], "-gaussian") == 0) {
            testFilterWindow(exam);
            run_main_qt_loop = true;
            continue;
        }
        if (strcmp(argv[readen_args], "-filters") == 0) {
            FilterDialog *dlg = new FilterDialog();

            FilterController *controler = new FilterController(dlg);
            ImageMask2d *slice = exam->getImageMask2d(0, CORONAL);
            GrayViewWindow& window = slice->getParams().getGrayViewWindow();
            window.setRange(HundsfieldValue::min(), HundsfieldValue::max());
            cout << "range : " << window.getMin()->getExamenValue() << ", " << window.getMax()->getExamenValue() << endl;
            /*controler->showMask(false);
            controler->showImage(true);*/
            controler->start(slice);
            delete slice; slice = NULL;

            dlg->show();
            run_main_qt_loop = true;
            continue;
        }

        if (strcmp(argv[readen_args], "-login") == 0) {
            testLogin();
            run_main_qt_loop = true;
            continue;
        }

        if (strcmp(argv[readen_args], "-snmi") == 0) {
            if (++readen_args >= argc) {
                usage(argv[0]);
                return EXIT_FAILURE;
            }
            string path = argv[readen_args];
            ParserNMi3D parser_nmi3d;
            //string filename = "../../result/test.nmi3d";
            // Save Image in NMI3D

            bool what = false;// = parser_nbmi3d.saveFile(path, &exam); /// TODO : document the booleans arguments!!!!!!!!!!!!!!!
            if (what == false) {
                cerr << "erreur sauvegarde nmi3d\n";
            }
            continue;
        }

        if (strcmp(argv[readen_args], "-onmi") == 0) {
            if (++readen_args >= argc) {
                usage(argv[0]);
                return EXIT_FAILURE;
            }
            delete exam;
            ParserNMi3D parser_nmi3d;
            string filename = argv[readen_args];
            exam = parser_nmi3d.loadFile(filename);
            eassert(exam != NULL);
            continue;
        }

        cerr << "Unknown parameter skipped : " << argv[readen_args] << endl;
    }

    int appResult = EXIT_SUCCESS;
    if (run_main_qt_loop) {
        appResult = app->exec();
    }

    // Clean and exit
    delete viewer; viewer = NULL;
    delete imageViewer; imageViewer = NULL;
    delete exam; exam = NULL;
    delete login; login = NULL;
    delete app; app = NULL;

    return appResult;
}
