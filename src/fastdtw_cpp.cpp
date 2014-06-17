#include <fastdtw_cpp/dtw.hpp>
#include <fastdtw_cpp/fastdtw.hpp>
#include <fastdtw_cpp/downsampling.hpp>

void TEST_1_projection2()
{
    std::cout << std::endl;

    fastdtw_cpp::projection::ProjectionIDC<1,2> p(4,4);
    fastdtw_cpp::path::WarpPath<float> path;
    path.push_back(0,0);
    path.push_back(0,1);
    path.push_back(1,2);
    path.push_back(2,3);
    path.push_back(3,3);
    p.project<float>(path);

    p.print_ascii();

    assert(p.min(0) == 0); assert(p.max(0) == 2);
    assert(p.min(1) == 0); assert(p.max(1) == 2);
    assert(p.min(2) == 0); assert(p.max(2) == 3);
    assert(p.min(3) == 0); assert(p.max(3) == 4);
    assert(p.min(4) == 0); assert(p.max(4) == 5);
    assert(p.min(5) == 0); assert(p.max(5) == 7);
    assert(p.min(6) == 1); assert(p.max(6) == 7);
    assert(p.min(7) == 2); assert(p.max(7) == 7);

    std::cout << std::endl;

}

void TEST_2_projection2()
{
    std::cout << std::endl;

    fastdtw_cpp::projection::ProjectionIDC<2,2> p(4,4);
    fastdtw_cpp::path::WarpPath<float> path;
    path.push_back(0,0);
    path.push_back(1,0);
    path.push_back(2,1);
    path.push_back(3,2);
    path.push_back(3,3);
    p.project<float>(path);

    p.print_ascii();

    assert(p.min(0) == 0); assert(p.max(0) == 7);
    assert(p.min(1) == 0); assert(p.max(1) == 7);
    assert(p.min(2) == 0); assert(p.max(2) == 7);
    assert(p.min(3) == 0); assert(p.max(3) == 7);
    assert(p.min(4) == 1); assert(p.max(4) == 7);
    assert(p.min(5) == 2); assert(p.max(5) == 7);
    assert(p.min(6) == 3); assert(p.max(6) == 7);
    assert(p.min(7) == 4); assert(p.max(7) == 7);

    std::cout << std::endl;

}

void TEST_3_projection2()
{
    std::cout << std::endl;

    fastdtw_cpp::projection::ProjectionIDC<0,2> p(4,4);
    fastdtw_cpp::path::WarpPath<float> path;
    path.push_back(0,0);
    path.push_back(1,1);
    path.push_back(2,2);
    path.push_back(3,3);
    p.project<float>(path);

    p.print_ascii();

    assert(p.min(0) == 0); assert(p.max(0) == 1);
    assert(p.min(1) == 0); assert(p.max(1) == 2);
    assert(p.min(2) == 1); assert(p.max(2) == 3);
    assert(p.min(3) == 2); assert(p.max(3) == 4);
    assert(p.min(4) == 3); assert(p.max(4) == 5);
    assert(p.min(5) == 4); assert(p.max(5) == 6);
    assert(p.min(6) == 5); assert(p.max(6) == 7);
    assert(p.min(7) == 6); assert(p.max(7) == 7);

    std::cout << std::endl;

    fastdtw_cpp::projection::ProjectionIDC<1,2> p1(4,4);
    p1.project<float>(path);

    p1.print_ascii();

    assert(p1.min(0) == 0); assert(p1.max(0) == 3);
    assert(p1.min(1) == 0); assert(p1.max(1) == 4);
    assert(p1.min(2) == 0); assert(p1.max(2) == 5);
    assert(p1.min(3) == 0); assert(p1.max(3) == 6);
    assert(p1.min(4) == 1); assert(p1.max(4) == 7);
    assert(p1.min(5) == 2); assert(p1.max(5) == 7);
    assert(p1.min(6) == 3); assert(p1.max(6) == 7);
    assert(p1.min(7) == 4); assert(p1.max(7) == 7);

    std::cout << std::endl;
}

void TEST_4_offsets()
{
    std::vector<unsigned int> offsets;
    fastdtw_cpp::utils::offset_vector<3>(1024, 10, offsets);
    assert(offsets.size() == 5);
    assert(offsets.at(0)  == 0);
    assert(offsets.at(1)  == 1);
    assert(offsets.at(2)  == 2);
    assert(offsets.at(3)  == 2);
    assert(offsets.at(4)  == 1);

}

void TEST_5_offsets()
{
    std::vector<unsigned int> offsets;
    fastdtw_cpp::utils::offset_vector<2>(1000, 42, offsets);
//    assert();
//    assert();
//    assert();
//    assert();
//    assert();
//    assert();
//    assert();
}


void TEST_mean() {

    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0};

    const double mean = fastdtw_cpp::utils::mean<double, 5>::perform(data);

    std::cout << "MEAN: " << mean << std::endl;

    assert(mean == 3.0);

}

void TEST_dot() {

    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0};

    const double dot = fastdtw_cpp::utils::dot<double, 5>::perform(data, data);

    std::cout << "DOT PRODUCT: " << dot << std::endl;

    assert(dot == 55.0);
}


void TEST_filterBox() {

    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0};

    const double result = fastdtw_cpp::utils::filter<double, FILTER_TYPE_BOX, 5>::perform(data);

    std::cout << "BOX RESULT: " << result << std::endl;

    assert(result == 3.0);

}

void TEST_filterBinomial() {

    double data[] = {1.0, 1.0, 2.0, 1.0, 1.0};

    double target = (
        (data[0] * fastdtw_cpp::utils::binomial_kernel<double, 5, 0>::value) +
        (data[1] * fastdtw_cpp::utils::binomial_kernel<double, 5, 1>::value) +
        (data[2] * fastdtw_cpp::utils::binomial_kernel<double, 5, 2>::value) +
        (data[3] * fastdtw_cpp::utils::binomial_kernel<double, 5, 3>::value) +
        (data[4] * fastdtw_cpp::utils::binomial_kernel<double, 5, 4>::value)
    );

    const double result = fastdtw_cpp::utils::filter<double, FILTER_TYPE_BINOMIAL, 5>::perform(data);

    std::cout << "BINOMIAL RESULT: " << result << std::endl;

    assert(result == target);

}

void TEST_downSamplingBox() {

    const double threshold = 10e-8;

    const double signal_data[]  = {0.0, 0.14206848155679283, 0.2785924396240553, 0.4042483814372735, 0.5141460638856562, 0.6040234401467309, 0.6704165621208917, 0.7107976651931819, 0.7236759303198054, 0.7086569063741399, 0.6664582237720257, 0.5988809729248656, 0.5087378885724815, 0.39974120306093336, 0.2763546395024042, 0.1436154453839865, 0.0069335615849674265, -0.12812406669868368, -0.25605543827864996, -0.37164285516695383, -0.47016094747703185, -0.5475650707356822, -0.6006525647984006, -0.6271904454828686, -0.626004438256948, -0.5970258044878397, -0.5412940934364601, -0.4609157102825408, -0.3589799519413895, -0.23943585805817785, -0.10693478674084442, 0.03335500896078746, 0.17595441158018277, 0.31529186297782735, 0.44592547343927225, 0.5627599613397896, 0.6612497746769358, 0.7375802966576286, 0.788819911245936, 0.813036866299172, 0.809376275328962, 0.7780941880711673, 0.7205473715796668, 0.6391392092406418, 0.5372238745440331, 0.4189725999025987, 0.2892073719598294, 0.15320868343107222, 0.016505005806360426, -0.11534762402500007, -0.23698711604129583, -0.3434591072506055, -0.43041448700683443, -0.49428279276750897, -0.532414563550609, -0.5431869759062946, -0.5260685510296581, -0.48164035334508454, -0.4115728354405376, -0.3185592524701558, -0.20620830058180006, -0.07890025953564261, 0.058387625347366454, 0.20027956043746795, 0.3412155099797852, 0.4756728474994516, 0.5983865158870784, 0.7045589190776744, 0.7900511776050819, 0.8515481232774598, 0.8866904551577149, 0.894168788207915, 0.8737758451759398, 0.8264147109994684, 0.7540628206511741, 0.6596931161169934, 0.5471555157308383, 0.4210234213102141, 0.28641138236975006, 0.14877118656592264, 0.013674505604327897, -0.11340923816786808, -0.2273309287254809, -0.32346704364100753, -0.39790398751578615, -0.44759412277359645, -0.4704772773605325, -0.465562885221794, -0.4329694848730029, -0.37392000138187087, -0.29069299985194286, -0.1865318537774314, -0.06551544943943793, 0.06760441904947453, 0.20759248150665238, 0.3489386982008542, 0.48607792066420297, 0.6136117496119013, 0.7265237451952661, 0.820379409835114};
    const double signal_data2_gt[] = {0.04735616051893094, 0.27496976753937385, 0.5074726284898868, 0.6617458891536014, 0.7143768339623757, 0.6579987010236771, 0.5024533548527601, 0.27323709598244134, 0.00747498009009008, -0.2519407867147625, -0.46312295779322254, -0.5918026936723171, -0.6167402294092188, -0.5330785360689468, -0.3531105067607027, -0.1043385452794116, 0.17486709450626586, 0.44132576591896305, 0.6538633442247845, 0.7798123580675789, 0.800169109899767, 0.7125935896304919, 0.5317785612290912, 0.28712955176450006, 0.018122021737477526, -0.2319312824389671, -0.42271879567498294, -0.5232947774081376, -0.5169652934270124, -0.4039241470852593, -0.20122260419586616, 0.059922308749730584, 0.3390559726389016, 0.5928727608214015, 0.7820527399867387, 0.8774691222143632, 0.8647864481277743, 0.7467235492558786, 0.5426240177193487, 0.2854019967486289, 0.016345484667460823, -0.22140240351145218, -0.38965505131013, -0.46121142845197427, -0.4241507904922226, -0.28371495167041505, -0.0614809613891316, 0.20804519958566037, 0.4828761228256528, 0.7201716348807605};
    const double signal_data3_gt[] = {0.12322736285907857, 0.48139609506095404, 0.678040474713218, 0.4778963839529595, 0.009590429785922963, -0.4356221460601007, -0.5805404863834942, -0.3301758627030204, 0.17061810504860575, 0.6250004894037755, 0.7641916858659459, 0.5105005675413611, 0.0244400970210035, -0.39264828517402917, -0.48139473930680304, -0.1817414808437983, 0.3306170140700112, 0.7507982076741677, 0.8296597065326721, 0.5249165212412854, 0.026781692634879173, -0.3574229610911855, -0.3896923902048706, -0.045716904491295424, 0.4703643190973579};
    const double signal_data4_gt[] = {0.2426169402597037, 0.5457776512423772, 0.017288222559593946, -0.4487794983822051, 0.15514757724978695, 0.6332309142703608, 0.04743079312944512, -0.3519281684415435, 0.29989124696679353, 0.7017914784827084, 0.06475841759499301, -0.26427741859578385};
    const double signal_data5_gt[] = {0.3436705105872615, 0.03809545847325532, 0.11319966437931422, 0.1095778463194208, 0.21658485233598612, 0.16742415916063919};

    const unsigned int signal_length  = sizeof(signal_data) / sizeof(double);
    const unsigned int signal_length2 = sizeof(signal_data2_gt) / sizeof(double);
    const unsigned int signal_length3 = sizeof(signal_data3_gt) / sizeof(double);
    const unsigned int signal_length4 = sizeof(signal_data4_gt) / sizeof(double);
    const unsigned int signal_length5 = sizeof(signal_data5_gt) / sizeof(double);

    double* signal_data2 = new double[signal_length2];
    double* signal_data3 = new double[signal_length3];
    double* signal_data4 = new double[signal_length4];
    double* signal_data5 = new double[signal_length5];

    fastdtw_cpp::utils::downSample<double, 2, FILTER_TYPE_BOX, 3>(signal_data, signal_length, signal_data2);
    fastdtw_cpp::utils::downSample<double, 2, FILTER_TYPE_BOX, 3>(signal_data2, signal_length2, signal_data3);
    fastdtw_cpp::utils::downSample<double, 2, FILTER_TYPE_BOX, 3>(signal_data3, signal_length3, signal_data4);
    fastdtw_cpp::utils::downSample<double, 2, FILTER_TYPE_BOX, 3>(signal_data4, signal_length4, signal_data5);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Downsampling outputs (BOX)" << std::endl;

    std::cout << std::endl;
    for (int i = 0; i < signal_length2; i++) {
        std::cout << signal_data2_gt[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < signal_length2; i++) {
        std::cout << signal_data2[i] << " ";
    }
    std::cout << std::endl;


    std::cout << std::endl;
    for (int i = 0; i < signal_length3; i++) {
        std::cout << signal_data3_gt[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < signal_length3; i++) {
        std::cout << signal_data3[i] << " ";
    }
    std::cout << std::endl;



    std::cout << std::endl;
    for (int i = 0; i < signal_length4; i++) {
        std::cout << signal_data4_gt[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < signal_length4; i++) {
        std::cout << signal_data4[i] << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl;
    for (int i = 0; i < signal_length5; i++) {
        std::cout << signal_data5_gt[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < signal_length5; i++) {
        std::cout << signal_data5[i] << " ";
    }
    std::cout << std::endl;




    for (int i = 0; i < signal_length2; i++) {
        const double diff = std::abs(signal_data2_gt[i] - signal_data2[i]);
        assert(diff <= threshold);
    }
    for (int i = 0; i < signal_length3; i++) {
        const double diff = std::abs(signal_data3_gt[i] - signal_data3[i]);
        assert(diff <= threshold);
    }
    for (int i = 0; i < signal_length4; i++) {
        const double diff = std::abs(signal_data4_gt[i] - signal_data4[i]);
        assert(diff <= threshold);
    }
    for (int i = 0; i < signal_length5; i++) {
        const double diff = std::abs(signal_data5_gt[i] - signal_data5[i]);
        assert(diff <= threshold);
    }

    delete[] signal_data2;
    delete[] signal_data3;
    delete[] signal_data4;
    delete[] signal_data5;
}


void TEST_downSamplingBinomial() {

    const double threshold = 10e-10;

    const double signal_data[]  = {0.0, 0.14206848155679283, 0.2785924396240553, 0.4042483814372735, 0.5141460638856562, 0.6040234401467309, 0.6704165621208917, 0.7107976651931819, 0.7236759303198054, 0.7086569063741399, 0.6664582237720257, 0.5988809729248656, 0.5087378885724815, 0.39974120306093336, 0.2763546395024042, 0.1436154453839865, 0.0069335615849674265, -0.12812406669868368, -0.25605543827864996, -0.37164285516695383, -0.47016094747703185, -0.5475650707356822, -0.6006525647984006, -0.6271904454828686, -0.626004438256948, -0.5970258044878397, -0.5412940934364601, -0.4609157102825408, -0.3589799519413895, -0.23943585805817785, -0.10693478674084442, 0.03335500896078746, 0.17595441158018277, 0.31529186297782735, 0.44592547343927225, 0.5627599613397896, 0.6612497746769358, 0.7375802966576286, 0.788819911245936, 0.813036866299172, 0.809376275328962, 0.7780941880711673, 0.7205473715796668, 0.6391392092406418, 0.5372238745440331, 0.4189725999025987, 0.2892073719598294, 0.15320868343107222, 0.016505005806360426, -0.11534762402500007, -0.23698711604129583, -0.3434591072506055, -0.43041448700683443, -0.49428279276750897, -0.532414563550609, -0.5431869759062946, -0.5260685510296581, -0.48164035334508454, -0.4115728354405376, -0.3185592524701558, -0.20620830058180006, -0.07890025953564261, 0.058387625347366454, 0.20027956043746795, 0.3412155099797852, 0.4756728474994516, 0.5983865158870784, 0.7045589190776744, 0.7900511776050819, 0.8515481232774598, 0.8866904551577149, 0.894168788207915, 0.8737758451759398, 0.8264147109994684, 0.7540628206511741, 0.6596931161169934, 0.5471555157308383, 0.4210234213102141, 0.28641138236975006, 0.14877118656592264, 0.013674505604327897, -0.11340923816786808, -0.2273309287254809, -0.32346704364100753, -0.39790398751578615, -0.44759412277359645, -0.4704772773605325, -0.465562885221794, -0.4329694848730029, -0.37392000138187087, -0.29069299985194286, -0.1865318537774314, -0.06551544943943793, 0.06760441904947453, 0.20759248150665238, 0.3489386982008542, 0.48607792066420297, 0.6136117496119013, 0.7265237451952661, 0.820379409835114};
    const double signal_data2_gt[] = {0.03551712038919821, 0.2758754355605442, 0.5091409873388292, 0.663913557395424, 0.7167016080517332, 0.6601135817107642, 0.5040244882826905, 0.27401648186243205, 0.007339625463809417, -0.25296944960573436, -0.46488245521417493, -0.5940151614538379, -0.6190562816211511, -0.5351324254108252, -0.35457786805587443, -0.1049876056447698, 0.1751389237747451, 0.44247569279904037, 0.6557099518378224, 0.7820642463621681, 0.8024709012570658, 0.7145820351177856, 0.5331398895578267, 0.28764900681333244, 0.01771776775469825, -0.2331952408395493, -0.4246427185079459, -0.5255747239437554, -0.5192411078276739, -0.4058363191740789, -0.20246902829234964, 0.05953863789913956, 0.33959585697412253, 0.5942511995878207, 0.7840523493913245, 0.8797744554502012, 0.8670337973898158, 0.7485583671047025, 0.543756892222221, 0.2856543431539092, 0.01567773990167759, -0.22288453481495937, -0.3917172853615441, -0.4635278906791138, -0.4263554640874177, -0.285459463715797, -0.06248958340170819, 0.20793202006590839, 0.4836765722852904, 0.7217596624593869};
    const double signal_data3_gt[] = {0.09560669918203471, 0.48951774190840663, 0.6893575888024137, 0.4855447600346443, 0.008931570796079133, -0.4441873803719806, -0.5918150375267414, -0.33731894179183597, 0.1719414836759402, 0.6339899607092133, 0.7753970209985214, 0.5171277052616928, 0.02247232537079491, -0.4020138504497991, -0.49247331469329547, -0.18780893446490965, 0.3332453878588013, 0.7605325884551677, 0.8406001043336337, 0.5304316236757635, 0.02353132203557625, -0.36746174905429035, -0.4004245706424366, -0.050626652613326245, 0.474261206773969};
    const double signal_data4_gt[] = {0.1940844598636277, 0.5884444198869696, 0.014805130313705506, -0.4912840993043248, 0.16013849656731444, 0.6754779269919873, 0.04001462638837089, -0.3936923535753249, 0.30980360742696517, 0.7430411051995497, 0.05250812967315639, -0.30473438573812245};
    const double signal_data5_gt[] = {0.29267444986946317, 0.03169264530251395, 0.12611770520557283, 0.09045370654835104, 0.24223899161953877, 0.135830744701935};

    const unsigned int signal_length  = sizeof(signal_data) / sizeof(double);
    const unsigned int signal_length2 = sizeof(signal_data2_gt) / sizeof(double);
    const unsigned int signal_length3 = sizeof(signal_data3_gt) / sizeof(double);
    const unsigned int signal_length4 = sizeof(signal_data4_gt) / sizeof(double);
    const unsigned int signal_length5 = sizeof(signal_data5_gt) / sizeof(double);

    double* signal_data2 = new double[signal_length2];
    double* signal_data3 = new double[signal_length3];
    double* signal_data4 = new double[signal_length4];
    double* signal_data5 = new double[signal_length5];

    fastdtw_cpp::utils::downSample<double, 2, FILTER_TYPE_BINOMIAL, 3>(signal_data, signal_length, signal_data2);
    fastdtw_cpp::utils::downSample<double, 2, FILTER_TYPE_BINOMIAL, 3>(signal_data2, signal_length2, signal_data3);
    fastdtw_cpp::utils::downSample<double, 2, FILTER_TYPE_BINOMIAL, 3>(signal_data3, signal_length3, signal_data4);
    fastdtw_cpp::utils::downSample<double, 2, FILTER_TYPE_BINOMIAL, 3>(signal_data4, signal_length4, signal_data5);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Downsampling outputs (BINOMIAL)" << std::endl;

    std::cout << std::endl;
    for (int i = 0; i < signal_length2; i++) {
        std::cout << signal_data2_gt[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < signal_length2; i++) {
        std::cout << signal_data2[i] << " ";
    }
    std::cout << std::endl;


    std::cout << std::endl;
    for (int i = 0; i < signal_length3; i++) {
        std::cout << signal_data3_gt[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < signal_length3; i++) {
        std::cout << signal_data3[i] << " ";
    }
    std::cout << std::endl;



    std::cout << std::endl;
    for (int i = 0; i < signal_length4; i++) {
        std::cout << signal_data4_gt[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < signal_length4; i++) {
        std::cout << signal_data4[i] << " ";
    }
    std::cout << std::endl;

    std::cout << std::endl;
    for (int i = 0; i < signal_length5; i++) {
        std::cout << signal_data5_gt[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < signal_length5; i++) {
        std::cout << signal_data5[i] << " ";
    }
    std::cout << std::endl;




    for (int i = 0; i < signal_length2; i++) {
        const double diff = std::abs(signal_data2_gt[i] - signal_data2[i]);
        assert(diff <= threshold);
    }
    for (int i = 0; i < signal_length3; i++) {
        const double diff = std::abs(signal_data3_gt[i] - signal_data3[i]);
        assert(diff <= threshold);
    }
    for (int i = 0; i < signal_length4; i++) {
        const double diff = std::abs(signal_data4_gt[i] - signal_data4[i]);
        assert(diff <= threshold);
    }
    for (int i = 0; i < signal_length5; i++) {
        const double diff = std::abs(signal_data5_gt[i] - signal_data5[i]);
        assert(diff <= threshold);
    }

    delete[] signal_data2;
    delete[] signal_data3;
    delete[] signal_data4;
    delete[] signal_data5;
}

int main(int argc, char *argv[])
{

    TEST_1_projection2();
    TEST_2_projection2();
    TEST_3_projection2();
    TEST_4_offsets();

    fastdtw_cpp::projection::ProjectionIDC<1,2> p2 (9,10);
    fastdtw_cpp::path::WarpPath<float> w2;
    w2.push_back(0,0);
    w2.push_back(0,1);
    w2.push_back(0,2);
    w2.push_back(1,2);
    w2.push_back(2,2);
    w2.push_back(3,3);
    w2.push_back(4,4);
    w2.push_back(4,5);
    w2.push_back(5,6);
    w2.push_back(6,6);
    w2.push_back(7,6);
    w2.push_back(8,6);
    w2.push_back(8,7);
    w2.push_back(9,8);

    p2.project<float>(w2);
    p2.print_ascii();


    std::vector<float> test;
    std::vector<float> test2;
    for(int i = 0 ; i < 128 ; ++i) {
        test.push_back(i);
        test2.push_back(i+1);
    }


    //    fastdtw_cpp::utils::SignalPyramid<float,2> s(test, 2);
    //    s.print();

    //    for(int i = 0 ; i < s.levelSize(0); ++i) {
    //        std::cout << s.levelPtr(0)[i] << std::endl;
    //    }

    fastdtw_cpp::path::WarpPath<float> path;
    float distance = 0;
    std::vector<bool> mask(128 * 128, true);
    fastdtw_cpp::dtw::apply(test, test2, mask, path);
    fastdtw_cpp::dtw::apply(test, test2, distance);
    std::cout << distance << std::endl;

    std::cout << path.getDistance() << std::endl;

    fastdtw_cpp::path::WarpPath<float> path2;
    fastdtw_cpp::fastdtw::apply(test, test2, 2, path2, 0);
    std::cout << path2.getDistance() << std::endl;

    TEST_mean();
    TEST_dot();

    TEST_filterBox();
    TEST_filterBinomial();

    TEST_downSamplingBox();
    TEST_downSamplingBinomial();

    //    path.print();
    //    std::cout << path.getDistance() << std::endl;
    //    std::cout << " --- " << std::endl;
    //    path2.print();

    return 0;
}

