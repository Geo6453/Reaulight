#include "mainwindow.h"
#include "OpenGL/openglwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    modelExplorer(nullptr),
    arborescence(new arborescence_projet(this)), // Initialisation de la classe arborescence_projet
    tabWidget(nullptr),
    dockGauche(nullptr)
{
    SoI = new Save_or_import();
    SoI->init(window());
    this->window()->setGeometry(0, 0, 1000, 600); // Taille de la fenêtre (L=1'000 ; l=600) à la position X=0 ; Y=0
    setCentralWidget(new QWidget);

    menuFichier = menuBar()->addMenu("&Fichier");
        QAction *actionImporter = new QAction("&Importer", this);
            menuFichier->addAction(actionImporter);
            connect(actionImporter, &QAction::triggered, this, [this]() {SoI->dialog(dialogType::import);});
        QMenu *fichiersRecents = menuFichier->addMenu("&Fichiers récents");
            fichiersRecents->addAction("Fichier bidon 1.txt");
            fichiersRecents->addAction("Fichier bidon 2.txt");
            fichiersRecents->addAction("Fichier bidon 3.txt");
        QAction *actionSauvegarder = new QAction("&Sauvegarder", this);
            menuFichier->addAction(actionSauvegarder);
            connect(actionSauvegarder, &QAction::triggered, this, [this]() {SoI->dialog(dialogType::saveIfOpen);});
        QAction *actionEnregistrerSous = new QAction("&Enregistrer sous", this);
            menuFichier->addAction(actionEnregistrerSous);
            connect(actionEnregistrerSous, &QAction::triggered, this, [this]() {SoI->dialog(dialogType::save);});
    menuFichier->addSeparator();
        QAction *actionQuitter = new QAction("&Quitter", this);
            menuFichier->addAction(actionQuitter);
            connect(actionQuitter, &QAction::triggered, qApp, &QApplication::quit);

    menuEdition = menuBar()->addMenu("&Edition");

    menuAffichage = menuBar()->addMenu("&Affichage 3D");

    menuAide = menuBar()->addMenu("&Aide");
        QAction *actionUpdate = new QAction("&Chercher des mises à jour", this);
            menuAide->addAction(actionUpdate);
            connect(actionUpdate, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/josephcab/Reaulight/releases"));});
        QAction *actionDépôtGithub = new QAction("&Dépôt Github", this);
            menuAide->addAction(actionDépôtGithub);
            connect(actionDépôtGithub, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/josephcab/Reaulight"));});
        QAction *actionDiscussionGithub = new QAction("&Salon de discussion Github", this);
            menuAide->addAction(actionDiscussionGithub);
            connect(actionDiscussionGithub, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/josephcab/Reaulight/discussions/10"));});
        QAction *actionDiscord = new QAction("&Serveur Discord", this);
            menuAide->addAction(actionDiscord);
            connect(actionDiscord, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://discord.gg/H7wEZ8mUKc"));});
    menuAide->addSeparator();
        QAction *actionQt = new QAction("&À propos de Qt", this);
            menuAide->addAction(actionQt);
            connect(actionQt, &QAction::triggered, this, [this] () {QMessageBox::aboutQt(this);});
        QAction *actionRéaulight = new QAction("&À propos de Réaulight", this);
            menuAide->addAction(actionRéaulight);
            connect(actionRéaulight, &QAction::triggered, this, []() {QDesktopServices::openUrl(QUrl("https://github.com/josephcab/Reaulight/blob/main/README.md"));});

    QAction *toggleTheme = new QAction("&Changer de thème", this);
    menuBar()->addAction(toggleTheme);

    // Initialisation des modèles
        modelExplorer = new QFileSystemModel(this);
        modelExplorer->setRootPath(QDir::homePath());
        modelExplorer->setFilter(QDir::Files | QDir::NoDotAndDotDot);
        modelExplorer->setNameFilters(QStringList() << "*.txt");

    // Création des vues
        QTreeView *treeExplorer = new QTreeView();
            treeExplorer->setModel(modelExplorer);
            treeExplorer->setRootIndex(modelExplorer->index(QDir::homePath()));
        QTreeView *treeArborescence = new QTreeView();
            treeArborescence->setModel(arborescence->getModel()); // Utilisation du modèle de arborescence_projet

    // Création des onglets
        tabWidget = new QTabWidget(this);
        tabWidget->addTab(treeExplorer, "Explorateur");
        tabWidget->addTab(treeArborescence, "Arborescence");
        tabWidget->setCurrentIndex(tabWidget->indexOf(treeArborescence));

    // Ajouter les onglets dans un QDockWidget
        dockGauche = new QDockWidget("Panneau latéral", this);
        dockGauche->setWidget(tabWidget);
        addDockWidget(Qt::LeftDockWidgetArea, dockGauche);
        dockGauche->setMinimumSize(200, 400);
        dockGauche->setMaximumSize(300, 500);
        dockGauche->setFeatures(dockGauche->features() & QDockWidget::NoDockWidgetFeatures);

    // Exemple d'ajout d'éléments à l'arborescence
        arborescence->addSpectacle("Spectacle 1");
        QStandardItem *spectacle1 = arborescence->getModel()->item(0); // Récupère le premier spectacle
            arborescence->addUnivers(spectacle1, "Univers 1");
            arborescence->addReseau(spectacle1, "Réseau 1");
            QStandardItem *univers1 = spectacle1->child(0); // Récupère le premier univers<
                arborescence->addMaterielDMX(univers1, "Matériel DMX 1");
        treeArborescence->expandAll();

    //recup les données pour l'enregristrer du fichier .json
    connect(SoI, &Save_or_import::isSavingAccept, this, [this](bool accepted)
    {
        if(accepted == true)
        {
            /** A corriger **/
            //SoI->setProjectorList(this->projector); //envoyer tout les projecteurs pour la sauvegarde
        }
    });

    // Création d'un QDockWidget bas
    dockBas = new QDockWidget("Panneau complémentaire", this);
    addDockWidget(Qt::BottomDockWidgetArea, dockBas);
    dockBas->setMinimumWidth(300);
    //dockBas->setMaximumWidth(600);
    dockBas->setFeatures(dockBas->features() & QDockWidget::NoDockWidgetFeatures);

    // Création du widget conteneur pour la grille
    QWidget *grille = new QWidget();  // La grille est déclarée comme un widget lambda
    dockBas->setWidget(grille);       // Assignation au dock

    // Création des boutons
    QLabel *labelType      = new QLabel("Type :", grille);
    QLabel *labelMarque    = new QLabel("Marque :", grille);
    QLabel *labelNom       = new QLabel("Nom :", grille);
    QLabel *labelModele    = new QLabel("Modèle :", grille);

    QComboBox *comboType   = new QComboBox(grille);
    QComboBox *comboMarque = new QComboBox(grille);
    QComboBox *comboNom    = new QComboBox(grille);
    QComboBox *comboModele = new QComboBox(grille);
    comboType->   addItem("");
    comboType->   addItem("placeholder");
    comboMarque-> addItem("");
    comboMarque-> addItem("placeholder");
    comboNom->    addItem("");
    comboNom->    addItem("placeholder");
    comboModele-> addItem("");
    comboModele-> addItem("placeholder");

    QLabel *labelCouleur   = new QLabel("Couleur", grille);
    QLabel *labelR         = new QLabel("R :", grille);
    QLabel *labelV         = new QLabel("V :", grille);
    QLabel *labelB         = new QLabel("B :", grille);
    QSpinBox *editR        = new QSpinBox(grille);
    QSpinBox *editV        = new QSpinBox(grille);
    QSpinBox *editB        = new QSpinBox(grille);

    labelCouleur->setMaximumWidth(200);
    labelR->setMaximumWidth(30);
    labelV->setMaximumWidth(30);
    labelB->setMaximumWidth(30);

    labelCouleur->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    labelR->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    labelV->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    labelB->setAlignment(Qt::AlignVCenter | Qt::AlignRight);

    editR->setMaximumWidth(100);
    editV->setMaximumWidth(100);
    editB->setMaximumWidth(100);

    editR->setRange(0, 255);
    editV->setRange(0, 255);
    editB->setRange(0, 255);

    editR->setWrapping(true);
    editV->setWrapping(true);
    editB->setWrapping(true);

    QFrame *colorViewer = new QFrame;
    auto updateColor = [=]()
    {
        QColor color(editR->value(), editV->value(), editB->value());
        QPalette palette = colorViewer->palette();
        palette.setColor(QPalette::Window, color);
        colorViewer->setPalette(palette);
    };
    connect(editR, QOverload<int>::of(&QSpinBox::valueChanged), updateColor);
    connect(editV, QOverload<int>::of(&QSpinBox::valueChanged), updateColor);
    connect(editB, QOverload<int>::of(&QSpinBox::valueChanged), updateColor);
    updateColor();
    colorViewer->setAutoFillBackground(true);

    QSlider *sliderFrequence = new QSlider(Qt::Horizontal, grille);
        sliderFrequence->setRange(0, 10);
        sliderFrequence->setSingleStep(1);
    QLabel *labelFrequence = new QLabel("Fréquence = OHz", grille);
        labelFrequence->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
        connect(sliderFrequence, &QSlider::valueChanged, this, [labelFrequence](int value)
            {
                labelFrequence->setText(QString("Fréquence = %1Hz").arg(value));
            });

    QSlider *sliderAngle = new QSlider(Qt::Horizontal, grille);
        sliderAngle->setRange(0, 359);
        sliderAngle->setSingleStep(1);
    QLabel *labelAngle = new QLabel("Angle = 0°", grille);
        labelAngle->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
        connect(sliderAngle, &QSlider::valueChanged, this, [labelAngle](int value)
            {
                labelAngle->setText(QString(" Angle = %1°").arg(value));
            });

    // Création du layout en grille et y ajoute les boutons
    QGridLayout *layout = new QGridLayout(grille);  // Maintenant la grille est déclarée comme QGridLayout
    layout->addWidget(labelType,       0, 0, 1, 1);
    layout->addWidget(labelMarque,     1, 0, 1, 1);
    layout->addWidget(labelNom,        2, 0, 1, 1);
    layout->addWidget(labelModele,     3, 0, 1, 1);

    layout->addWidget(comboType,       0, 1, 1, 1);
    layout->addWidget(comboMarque,     1, 1, 1, 1);
    layout->addWidget(comboNom,        2, 1, 1, 1);
    layout->addWidget(comboModele,     3, 1, 1, 1);

    // Ajoute un séparateur vertical
    QFrame *separator1 = new QFrame();
    separator1->setFrameStyle(QFrame::VLine | QFrame::Sunken);
    layout->addWidget(separator1,      0, 2, 4, 1);

    layout->addWidget(labelCouleur,    0, 3, 1, 2);

    layout->addWidget(labelR,          1, 3, 1, 1);
    layout->addWidget(editR,           1, 4, 1, 1);

    layout->addWidget(labelV,          2, 3, 1, 1);
    layout->addWidget(editV,           2, 4, 1, 1);

    layout->addWidget(labelB,          3, 3, 1, 1);
    layout->addWidget(editB,           3, 4, 1, 1);

    layout->addWidget(colorViewer,     1, 5, 3, 1);

    QFrame *separator2 = new QFrame();
    separator2->setFrameStyle(QFrame::VLine | QFrame::Sunken);
    layout->addWidget(separator2,      0, 9, 4, 1);

    layout->addWidget(labelFrequence,  0, 10, 1, 2);
    layout->addWidget(labelAngle,      0, 12, 1, 2);
    layout->addWidget(sliderFrequence, 1, 10, 1, 2);
    layout->addWidget(sliderAngle,     1, 12, 1, 2);
}

MainWindow::~MainWindow() {}
