#include <iostream>
#include <math.h>

#include "energy.h"
#include "particle.h"
#include "state.h"
#include "colloid.h"
#include "sphere.h"
#include "tunablecrystal.h"
#include "tunablecluster.h"

#include "crystalmanager.h"
#include "realcrystalbuilder.h"
#include "virtualcrystalbuilder.h"
#include "rotatingelectricfield.h"
#include "homogemiusfield.h"

#include "crystaldipolemethod.h"
#include "clusterdipolemethod.h"
#include "deformationmethod.h"
#include "colloidmodel.h"

#include "crystalelementmethod.h"
#include "clusterelementmethod.h"
#include "clusterenergymethod.h"
#include "surfacepolarizationequation.h"
#include "conductorscreeningmodel.h"

#include "sequentialshiftmethod.h"

#include "optimizationalgorithm.h"

#include "tucomethod.h"
#include "electricmesh.h"
#include "symplexintegration.h"
#include "montecarlointegration.h"

#include "crystaldeformationmethod.h"
#include "dipolesequentialshiftmethod.h"
#include "bemsequentialshiftmethod.h"
#include "configuration.h"

namespace tuco {

class RunManager
{
    cs::CrystalManager* crystalManager;
public:
    RunManager() :
        crystalManager(new cs::CrystalManager)
    {

    }
    void setUserInitialization()
    {

    }
    void setCrystalBuilders(cs::StructureBuilder* structureBuilder, cs::CrystalBuilder* crystalBuilder)
    {
        crystalManager->setStructureBuilder(structureBuilder);
        crystalManager->setCrystalBuilder(crystalBuilder);
        crystalManager->constructCrystal();
    }
};

}


#include "reactionfieldmethod.h"
#include "plane.h"
#include "curve.h"


void computerUnitAnisotropicParticle()
{
//**//////////////////////////////////////////////////////////////////////////**//
    using namespace ph;
    using namespace tuco;
    std::cout << "Test for OpenTuCo for pair potential" << std::endl;


//**Задаем внешнюю среду:
    std::cout << "                 / Create environment & fields" << std::endl;
    HomogeneousRotatingField* field = new HomogeneousRotatingField(1, Vector3d(1.0, 0.0, 0.0), 20, M_PI);
    //Environment* environment = new Environment(new Vacuum);
    Environment* environment = new Environment(new Material(10.0));
    environment->setElectricField(field);

//**Задаем коллоидные частицы:
    std::cout << "                 / Create colloidal particle" << std::endl;
    Object* object = new Object(new Sphere("Ellipse-2", 1.0), new Material(1.0));
    //Object* object = new Object(new Sphere("shell", 1.0), new Material(1.0));

    Colloid* colloid1 = new Colloid(1, new State(1, Vector3d(0.0, 0.0, 0.0), M_PI / 2.0), object);
    colloid1->setPhysicalMesh(new ElectricMesh);


//**Задаем коллоидный кластер:
    std::cout << "                 / Create colloidal cluster" << std::endl;
    TunableCluster* tunableCluster = new TunableCluster(environment);
    tunableCluster->setMacroParticle(colloid1);

//**Задаем метод расчета поля:
    std::cout << "                 / Computer dipoles" << std::endl;

    IntegralEquation* equation = new SurfacePolarizationEquation("shell", new SymplexIntegration("cubic"), new SymplexIntegration("quadratic"));
    ClusterElementMethod* bem = new ClusterElementMethod("sphere", tunableCluster, equation);

/*
    //IntegralEquation* shellEquation = new SurfacePolarizationEquation("shell", new SymplexIntegration("cubic"), new MonteCarloIntegration("mc", 500));
    IntegralEquation* shellEquation = new SurfacePolarizationEquation("shell", new SymplexIntegration("cubic"), new SymplexIntegration("quadratic"));
    IntegralEquation* coreEquation = new SurfacePolarizationEquation("core", new SymplexIntegration("cubic"), new SymplexIntegration("quadratic"));
    ClusterElementMethod* bem = new ClusterElementMethod("sphere", tunableCluster, shellEquation, coreEquation);
*/
//**Производим расчет поля:
    BEMReactionFieldMethod* rfm = new BEMReactionFieldMethod(tunableCluster, bem, field);
    Line* line = new Line(new Point(1, Vector3d(-5.0, 0.0, 0.0)), new Point(1, Vector3d(5.0, 0.0, 0.0)));
    line->setPointList(1000);
    rfm->computerReactionField(line);
    rfm->record("", "pot_field-d_mesh-ICS2-gQc-mQq_surf-gQc-mQq");

    std::cout << "END!" << std::endl;
}

void computerUnitParticle()
{
//**//////////////////////////////////////////////////////////////////////////**//
    using namespace ph;
    using namespace tuco;
    std::cout << "Test for OpenTuCo for pair potential" << std::endl;

//**Задаем внешнюю среду:
    std::cout << "                 / Create environment & fields" << std::endl;
    HomogeneousRotatingField* field = new HomogeneousRotatingField(1, Vector3d(1.0, 0.0, 0.0), 20, M_PI);
    //Environment* environment = new Environment(new Vacuum);
    Environment* environment = new Environment(new Material(10.0));
    environment->setElectricField(field);

//**Задаем коллоидные частицы:
    std::cout << "                 / Create colloidal particle" << std::endl;
    Object* object = new Object(new Sphere("shell", 1.0), new Material(1.0));
    Object* core = new Object(new Sphere("core500", 0.5), new Material(10.0));

    Colloid* colloid1 = new Colloid(1, new State(1, Vector3d(0.0, 0.0, 0.0)), object);
    colloid1->setPhysicalMesh(new ElectricMesh);
    colloid1->setCoreLinker(new CoreLinker(core, new ElectricMesh, new CoulombKernal));

//**Задаем коллоидный кластер:
    std::cout << "                 / Create colloidal cluster" << std::endl;
    TunableCluster* tunableCluster = new TunableCluster(environment);
    tunableCluster->setMacroParticle(colloid1);

//**Задаем метод расчета поля:
    std::cout << "                 / Computer dipoles" << std::endl;
/*
    IntegralEquation* equation = new SurfacePolarizationEquation("shell", new SymplexIntegration("cubic"), new SymplexIntegration("quadratic"));
    ClusterElementMethod* bem = new ClusterElementMethod("sphere", tunableCluster, equation);
*/

    //IntegralEquation* shellEquation = new SurfacePolarizationEquation("shell", new SymplexIntegration("cubic"), new MonteCarloIntegration("mc", 500));
    IntegralEquation* shellEquation = new SurfacePolarizationEquation("shell", new SymplexIntegration("cubic"), new SymplexIntegration("quadratic"));
    IntegralEquation* coreEquation = new SurfacePolarizationEquation("core", new SymplexIntegration("cubic"), new SymplexIntegration("quadratic"));
    ClusterElementMethod* bem = new ClusterElementMethod("sphere", tunableCluster, shellEquation, coreEquation);

//**Производим расчет поля:
    BEMReactionFieldMethod* rfm = new BEMReactionFieldMethod(tunableCluster, bem, field);
    Line* line = new Line(new Point(1, Vector3d(-5.0, 0.0, 0.0)), new Point(1, Vector3d(5.0, 0.0, 0.0)));
    line->setPointList(1000);
    rfm->computerReactionField(line);
    rfm->record("", "pot_field-d_mesh-ICS2-gQc-mQq_surf-gQc-mQq");

    std::cout << "END!" << std::endl;
}

void computerSystemOfParticles()
{
//**//////////////////////////////////////////////////////////////////////////**//
    using namespace ph;
    using namespace tuco;
    std::cout << "Test for OpenTuCo for pair potential" << std::endl;

//**Create external field:
//**    type of electric field|: in-plane rotating;
//**    normal of electric strength, |E|: 1.0;
//**    count of point on hodograph, N: 20;
//**    angle of rotation for meaning, phi_m: pi/2;
    std::cout << "                 / Create environment & fields" << std::endl;
    HomogeneousRotatingField* field = new HomogeneousRotatingField(1, Vector3d(1.0, 0.0, 0.0), 20, M_PI);
    //HomogeneousRotatingField* field = new HomogeneousRotatingField(1, Vector3d(1e3, 0.0, 0.0), 10, M_PI / 2.0, 10, M_PI / 2.0); // 3D

//**Create environment:
    Environment* environment = new Environment(new Material(0.1)); //3.854
    environment->setElectricField(field);

//**Задаем коллоидные частицы:
    //object->setBoundaryElements();  // добавляем граничные элементы на объект;
    std::cout << "                 / Create colloidal particle" << std::endl;
    Object* object = new Object(new Sphere("shell", 1.0), new Material(1.0));
    Object* core = new Object(new Sphere("core900", 0.9), new Material(10.0));


    Colloid* colloid1 = new Colloid(1, new State(1, Vector3d(0.0, 0.0, 0.0)), object);
    colloid1->setPhysicalMesh(new ElectricMesh);
    colloid1->setCoreLinker(new CoreLinker(core, new ElectricMesh, new CoulombKernal));
    //colloid1->setPhysicalModel(   "dlvo", new DLVOModel(environment, 3.0));  //(?)радиус обрезки
    //colloid1->setPhysicalModel("elastic", new InversePowerLaw(24, 1e5, 2.1));  //(?)радиус обрезки
    Colloid* colloid2 = new Colloid(2, new State(1, Vector3d(0.0, 0.0, 0.0)), object);
    colloid2->setPhysicalMesh(new ElectricMesh);
    colloid2->setCoreLinker(new CoreLinker(core, new ElectricMesh, new CoulombKernal));
    //colloid2->setPhysicalModel(   "dlvo", new DLVOModel(environment, 3.0));  //(?)радиус обрезки
    //colloid2->setPhysicalModel("elastic", new InversePowerLaw(24, 1e5, 2.1));  //(?)радиус обрезки
/*
    Colloid* colloid3 = new Colloid(3, new State(1, Vector3d(0.0, 0.0, 0.0)), object);
    colloid3->setPhysicalMesh(new ElectricMesh);
    colloid3->setCoreLinker(new CoreLinker(core, new ElectricMesh, new CoulombKernal));
*/
//**Задаем коллоидный кластер:
    std::cout << "                 / Create colloidal cluster" << std::endl;
    TunableCluster* tunableCluster = new TunableCluster(environment);
    tunableCluster->setMacroParticle(colloid1);
    tunableCluster->setMacroParticle(colloid2);
    //tunableCluster->setMacroParticle(colloid3);
/*
    colloidCluster->record("", "test-tuco1");
    colloidCrystal->setVariation(new VirtualShift(1, Vector3d(0.1, .0, .0)));
    colloidCrystal->record("", "test-tuco2");
    std::cin.get();
*/
//**Расчет управляемого потенциала:
/*
    Vector3d E;
    std::string fullAddress = "field.txt";
    std::ofstream out(fullAddress, std::ios::out | std::ios::binary);
    while(!field->isFinish()) {
        field->rotateElectricFeild();
        E = field->getDirection();
        out << E(0) << " " << E(1) << " " << E(2) << std::endl;
    }
    out.close();
    std::cin. get();
*/

    std::cout << "                 / Computer dipoles" << std::endl;
    //ClusterDipoleMethod* cdm = new ClusterDipoleMethod(tunableCluster, new MutualDipoleModel);
    //DipoleSequentialShiftMethod* dssm = new DipoleSequentialShiftMethod(new Pair("P1"), tunableCluster, field, cdm);
    //DipoleSequentialShiftMethod* dssm = new DipoleSequentialShiftMethod(new tuco::Triplet("T2"), tunableCluster, field, cdm);

//**Simple particle:
/*
    IntegralEquation* shellEquation = new SurfacePolarizationEquation("shell", new SymplexIntegration("cubic"), new SymplexIntegration("quadratic"));
    ClusterElementMethod* bem = new ClusterElementMethod("sphere", tunableCluster, shellEquation);
*/
//**Composit particle:

    //IntegralEquation* shellEquation = new SurfacePolarizationEquation("shell", new SymplexIntegration("cubic"), new MonteCarloIntegration("mc", 50000));
    IntegralEquation* shellEquation = new SurfacePolarizationEquation("shell", new SymplexIntegration("cubic"), new SymplexIntegration("quadratic"));
    IntegralEquation* coreEquation = new SurfacePolarizationEquation("core", new SymplexIntegration("cubic"), new SymplexIntegration("quadratic"));
    //IntegralEquation* coreEquation = new ConductorScreeningModel("core", new SymplexIntegration("cubic"), new SymplexIntegration("quadratic"));
    ClusterElementMethod* bem = new ClusterElementMethod("sphere", tunableCluster, shellEquation, coreEquation);

//**Calculating of th e potential:
    BEMSequentialShiftMethod* dssm = new BEMSequentialShiftMethod(new Pair("P1"), tunableCluster, field, bem);
    //BEMSequentialShiftMethod* dssm = new BEMSequentialShiftMethod(new Triplets("T2"), tunableCluster, field, bem);

    //ClusterEnergyMethod* bem = new ClusterEnergyMethod(tunableCluster, new SymplexIntegration("quadratic"), new SymplexIntegration("quadratic"));
    //BEMSequentialShiftMethod* dssm = new BEMSequentialShiftMethod(new Pair("P1"), tunableCluster, field, bem);


    //dssm->setLogarithmicScale(10, 2.01, 2.4);
    //dssm->setLogarithmicScale(10, 2.4, 6.0);
    dssm->setDoubleLogarithmicScale(10, 10, 2.01, 2.4, 6.0);
    dssm->computerTunablePotential();
    dssm->getTunablePotentail()->record("", "pot_z2_beta-09_epsc-10_epsm-01");
    //dssm->getTunablePotentail()->record("", "pot_z2_beta-00_epsc-10_neg-P2");
    //dssm->getTunablePotentail()->record("", "pot_z3_beta-00_epsc-10_neg-T2-2");

    /*
    dssm->setLogarithmicScale(3, 4.0, 10.0);
    dssm->computerTunablePotential();
    dssm->getTunablePotentail()->record("", "pot_z2_beta-09_epsc-10_epsm-10_p3-long");
    */

    std::cout << "END!" << std::endl;

}

void computerSystemOfNIParticles()
{
//**//////////////////////////////////////////////////////////////////////////**//
    using namespace ph;
    using namespace tuco;
    std::cout << "Test for OpenTuCo for pair potential" << std::endl;

//**Create external field:
//**    type of electric field|: in-plane rotating;
//**    normal of electric strength, |E|: 1.0;
//**    count of point on hodograph, N: 20;
//**    angle of rotation for meaning, phi_m: pi/2;
    std::cout << "                 / Create environment & fields" << std::endl;
    HomogeneousRotatingField* field = new HomogeneousRotatingField(1, Vector3d(1.0, 0.0, 0.0), 20, M_PI / 2.0);
    //HomogeneousRotatingField* field = new HomogeneousRotatingField(1, Vector3d(1e3, 0.0, 0.0), 10, M_PI / 2.0, 10, M_PI / 2.0); // 3D

//**Create environment:
    Environment* environment = new Environment(new Cyclohexane);
    environment->setElectricField(field);

//**Задаем коллоидные частицы:
    std::cout << "                 / Create colloidal particle" << std::endl;
    Object* object = new Object(new Sphere("shell", 1.0), new Plexiglas);

    double concentration  = 100;
    Object* objectCore = new Object(new Sphere("core500", 0.5), new Plexiglas);
    NanoInclusionCore* nicore = new NanoInclusionCore(objectCore, concentration);
    nicore->setNanoInclusion();
    nicore->record("", "nicolloid");

    std::cin.get();
    Object* core = new Object(new Sphere("core900", 0.9), new Ethanol);

    Colloid* colloid1 = new Colloid(1, new State(1, Vector3d(0.0, 0.0, 0.0)), object);
    colloid1->setPhysicalMesh(new ElectricMesh);
    colloid1->setCoreLinker(new CoreLinker(core, new ElectricMesh, new CoulombKernal));
    //colloid1->setPhysicalModel(   "dlvo", new DLVOModel(environment, 3.0));  //(?)радиус обрезки
    //colloid1->setPhysicalModel("elastic", new InversePowerLaw(24, 1e5, 2.1));  //(?)радиус обрезки
    Colloid* colloid2 = new Colloid(2, new State(1, Vector3d(0.0, 0.0, 0.0)), object);
    colloid2->setPhysicalMesh(new ElectricMesh);
    colloid2->setCoreLinker(new CoreLinker(core, new ElectricMesh, new CoulombKernal));
    //colloid2->setPhysicalModel(   "dlvo", new DLVOModel(environment, 3.0));  //(?)радиус обрезки
    //colloid2->setPhysicalModel("elastic", new InversePowerLaw(24, 1e5, 2.1));  //(?)радиус обрезки
    //Colloid* colloid3 = new Colloid(3, new State(1, Vector3d(0.0, 0.0, 0.0)), object);

    std::cin.get();
//**Задаем коллоидный кластер:
    std::cout << "                 / Create colloidal cluster" << std::endl;
    TunableCluster* tunableCluster = new TunableCluster(environment);
    tunableCluster->setMacroParticle(colloid1);
    tunableCluster->setMacroParticle(colloid2);
    //tunableCluster->setMacroParticle(colloid3);
/*
    colloidCluster->record("", "test-tuco1");
    colloidCrystal->setVariation(new VirtualShift(1, Vector3d(0.1, .0, .0)));
0    colloidCrystal->record("", "test-tuco2");
    std::cin.get();
*/
//**Расчет управляемого потенциала:
/*
    Vector3d E;
    std::string fullAddress = "field.txt";
    std::ofstream out(fullAddress, std::ios::out | std::ios::binary);
    while(!field->isFinish()) {
        field->rotateElectricFeild();
        E = field->getDirection();
        out << E(0) << " " << E(1) << " " << E(2) << std::endl;
    }
    out.close();
    std::cin. get();
*/

    std::cout << "                 / Computer dipoles" << std::endl;
    //ClusterDipoleMethod* cdm = new ClusterDipoleMethod(tunableCluster, new MutualDipoleModel);
    //DipoleSequentialShiftMethod* dssm = new DipoleSequentialShiftMethod(new Pair("P1"), tunableCluster, field, cdm);
    //DipoleSequentialShiftMethod* dssm = new DipoleSequentialShiftMethod(new tuco::Triplet("T2"), tunableCluster, field, cdm);

//**Simple particle:
    //IntegralEquation* shellEquation = new ConductorScreeningModel("shell", new SymplexIntegration("cubic"), new SymplexIntegration("quadratic"));
//**Composit particle:
    //IntegralEquation* shellEquation = new SurfacePolarizationEquation("shell", new SymplexIntegration("cubic"), new MonteCarloIntegration("mc", 50000));
    IntegralEquation* shellEquation = new SurfacePolarizationEquation("shell", new SymplexIntegration("cubic"), new SymplexIntegration("quadratic"));
    IntegralEquation* coreEquation = new SurfacePolarizationEquation("core", new SymplexIntegration("quadratic"), new SymplexIntegration("quadratic"));
    //IntegralEquation* coreEquation = new ConductorScreeningModel("core", new SymplexIntegration("cubic"), new SymplexIntegration("quadratic"));
    ClusterElementMethod* bem = new ClusterElementMethod("-", tunableCluster, shellEquation, coreEquation);
    //ClusterElementMethod* bem = new ClusterElementMethod("sphere", tunableCluster, shellEquation);

//**Calculating of th e potential:
    BEMSequentialShiftMethod* dssm = new BEMSequentialShiftMethod(new Pair("P1"), tunableCluster, field, bem);

    //ClusterEnergyMethod* bem = new ClusterEnergyMethod(tunableCluster, new SymplexIntegration("quadratic"), new SymplexIntegration("quadratic"));
    //BEMSequentialShiftMethod* dssm = new BEMSequentialShiftMethod(new Pair("P1"), tunableCluster, field, bem);

    //dssm->setLogarithmicScale();
    //dssm->computerPairPotential();
    //dssm->getTunablePotentail()->record("", "pair_cdm");

    //dssm->setDoubleLogarithmicScale();
    dssm->computerTunablePotential();
    dssm->getTunablePotentail()->record("", "pot_t2_beta-9_ein-60");
    //dssm->getTunablePotentail()->record("", "int_field-R100_mesh-ICS2-gQc-mQq_surf-gQc-mQq");
    //dssm->getTunablePotentail()->record("", "Sd1um-Cm900nm_R20_mICS2-mQc-mQq_cQc-cQq");


    std::cout << "END!" << std::endl;

}


void test2()
{
    using namespace cs;
    using namespace ph;

//**Собираем виртуальный(реальный) кристалл, посредством менеджера кристаллов:
    CrystalManager* manager = new CrystalManager();
    manager->setStructureBuilder(new HexagonalStructureBuilder());
    //manager->setStructureBuilder(new GrapheneStructureBuilder());
    manager->setCrystalBuilder(new VirtualCrystalBuilder());
    manager->constructCrystal();

//**//////////////////////////////////////////////////////////////////////////**//
    using namespace tuco;
    std::cout << "Test for OpenTuCo" << std::endl;

//**Задаем коллоидный кристалл:
    std::cout << "                 / Create enviroment & fields" << std::endl;
    HomogeneousRotatingField* field = new HomogeneousRotatingField(1, Vector3d(1e3, 0.0, 0.0), 20, M_PI);
    Environment* environment = new Environment(new Water);
    environment->setElectricField(field);

//**Задаем коллоидные частицы:
    std::cout << "                 / Create colloidal particle" << std::endl;
    Object* object = new Object(new Sphere(1.0),
                                                 new SiliconDioxide);

    Colloid* colloid1 = new Colloid(1, object);
    //colloid1->setPhysicalModel(   "dlvo", new DLVOModel(environment, 3.0));  //(?)радиус обрезки
    //colloid1->setPhysicalModel("elastic", new InversePowerLaw(24, 1.0, 2.1));  //(?)радиус обрезки
    Colloid* colloid2 = new Colloid(2, object);
    //colloid2->setPhysicalModel(   "dlvo", new DLVOModel(environment, 3.0));  //(?)радиус обрезки
    //colloid2->setPhysicalModel("elastic", new InversePowerLaw(24, 1.0, 2.1));  //(?)радиус обрезки

//**Задаем коллоидный кристалл:
    std::cout << "                 / Create colloidal crytsal" << std::endl;
    TunableCrystal* colloidCrystal = new TunableCrystal(manager->getCrystal(), environment);
    colloidCrystal->setMacroParticle(colloid1);
    colloidCrystal->setMacroParticle(colloid2);
/*
    colloidCrystal->record("", "test-tuco1");
    colloidCrystal->setVariation(new VirtualShift(1, Vector3d(0.1, .0, .0)));
    colloidCrystal->record("", "test-tuco2");
    std::cin.get();
*/
//**Расчет первчиной коллоидной энергии:

//**Расчет управляемого взаимодействия:
//**Заполнение частиц кристалла диполями:

    //IntegralEquation* intergalEquation = new SurfacePolarizationEquation(new SymplexIntegration("quadratic"), new SymplexIntegration("quadratic"));

    //CrystalElementMethod* bem = new CrystalElementMethod(colloidCrystal, intergalEquation);
    //bem->computer(field);

    //std::cin.get();
    //std::cout << "                 / Computer dipoles" << std::endl;
    CrystalDipoleMethod* cdm = new CrystalDipoleMethod(colloidCrystal, new MutualDipoleModel);
/*
    while(!field->isFinish()) {
        cdm->computer(field);
        colloidCrystal->computerTunableEnergy();
        field->rotateElectricFeild();
    }
*/

//**Метод однородных деформаций:
    std::cout << "                 / Computer elastic modules" << std::endl;
    TunableDeformationMethod* idm = new TunableDeformationMethod(colloidCrystal, field, cdm, 0.005);
    idm->computerElasticModules();
    std::cout << colloidCrystal->getElasticModulus()->getModule(1) << std::endl;
}

#include "atom.h"
#include "atomcrystal.h"
#include "bornvonkarman.h"

void test_BvK()
{
    using namespace cs;
    using namespace atom;
    using namespace phonon;

//**Собираем виртуальный(реальный) кристалл, посредством менеджера кристаллов:
    CrystalManager* manager = new CrystalManager();
    manager->setStructureBuilder(new HexagonalStructureBuilder());
    //manager->setStructureBuilder(new GrapheneStructureBuilder());
    manager->setCrystalBuilder(new RealCrystalBuilder());
    manager->constructCrystal();

    manager->getCrystal()->setBrillouinZone();
    manager->getCrystal()->getBrillouinZone()->setBrillouinZone(150);
    manager->getCrystal()->getBrillouinZone()->setDirection("G-K-M-G", 50);
    manager->getCrystal()->getBrillouinZone()->record("", "test-BvK1");

    Atom* atom1 = new Atom(1, new Ferrum());
    atom::LennardJones* potential = new atom::LennardJones(1.0, 1.0);
    atom1->setInterPotential(1, potential);

    AtomCrystal* atomCrystal = new AtomCrystal(manager->getCrystal());
    atomCrystal->setAtom(atom1);
    atomCrystal->record("", "test-atom1");

    BornVonKarman* bvk = new BornVonKarman(atomCrystal);
    PhononSpectrum* ps = bvk->getPhononSpectrum();
    ps->record("", "simply");


}

#include "processing.h"
#include "wienermethod.h"
#include "hartmanmethod.h"
#include "dynamicstructurefactor.h"

void test_MD()
{
    using namespace cs;
    using namespace atom;
    using namespace phonon;
    using namespace pr;

//**Собираем виртуальный(реальный) кристалл, посредством менеджера кристаллов:
    CrystalManager* manager = new CrystalManager();
    manager->setStructureBuilder(new HexagonalStructureBuilder());
    //manager->setStructureBuilder(new GrapheneStructureBuilder());
    manager->setCrystalBuilder(new RealCrystalBuilder());
    manager->constructCrystal();

    manager->getCrystal()->setBrillouinZone();
    manager->getCrystal()->getBrillouinZone()->setBrillouinZone(150);
    manager->getCrystal()->getBrillouinZone()->setDirection("G-K", 20);
    manager->getCrystal()->getBrillouinZone()->record("", "test-BvK1");

    Atom* atom1 = new Atom(1, new Ferrum());
    atom::LennardJones* potential = new atom::LennardJones(1.0, 1.0);
    atom1->setInterPotential(1, potential);

    AtomCrystal* atomCrystal = new AtomCrystal(manager->getCrystal());
    atomCrystal->setAtom(atom1);
    atomCrystal->record("", "test-atom1");

    ProcessingLammps* prlammps = new ProcessingLammps("input/data_dump_2");
    prlammps->fineTuning(10, 1000);
    prlammps->setEnsemble();

    Direction* direction = manager->getCrystal()->getBrillouinZone()->getDirection(0);
    DynamicStructureFactor* dsf = new DynamicStructureFactor(direction, prlammps->getEnsemble());
    dsf->computer();
    dsf->record("", "test-DSF");
    //FourierEnsemble* fensemble = new FourierEnsemble(prlammps->getEnsemble(), &direction);
    //fensemble->setFourierEnsemble();
    std::cin.get();
    //VelocityAutocorrelationFunction* vaf = new VelocityAutocorrelationFunction(prlammps->getEnsemble());
    //vaf->computer();
    //vaf->record("", "test-VAF");

    DensityCorrelationFunction* dcf = new DensityCorrelationFunction(prlammps->getEnsemble());
    dcf->computer(direction);
    dcf->record("", "test-DCF");
    //WienerMethod* wm = new WienerMethod(prlammps);
    //Direction direction = manager->getCrystal()->getBrillouinZone()->getDirections()[0];
    //wm->getPowerSpectraDensity(&direction, "test_WM");

/*
    prlammps->shiftPhysState();
    prlammps->shiftPhysState();
    ph::PhysState* state = prlammps->load();
    for (auto& iPoint : *state->getMaterialPoints())
    {
        std::cout << iPoint.getPosition() << std::endl;
    }
*/
}




int main()
{
/*
    ph::RosenbrockFunctional* functional = new ph::RosenbrockFunctional;
    VectorXd r0 = Vector3d(2.0, 1.5, 0.0);
    cs::MethodGradientDescent* mgd = new cs::MethodGradientDescent(r0, functional);
    mgd->findMinimum();
    std::cout << functional->getArgumentVector() << std::endl;
    std::cin.get();
*/

    //test0();
    //computerUnitParticle();
    //computerSystemOfParticles();
    computerUnitAnisotropicParticle();
    //test2();
    //test_BvK();
    //test_MD();
    //std::cin.get();



    return EXIT_SUCCESS;
}


//int k = 1;
//long l = 8;
//std::cout << typeid (static_cast<decltype(k)>(l)).name() << std::endl;
//std::cout << typeid(k).name() << std::endl;
