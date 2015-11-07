#include "Server.h"

Server::Server()
{
	game = new Game(this);

	errorDialog = NULL;
	setWindowTitle("Fight In Square - server");

	port = new QLineEdit(this);
	logs = new QTextEdit(this);
	logs->setReadOnly(true);
	startButton = new QPushButton("Uruchom",this);
	stopButton = new QPushButton("Zatrzymaj",this);
	stopButton->hide();

	QVBoxLayout *lay= new QVBoxLayout();
	lay->addWidget(port);
	lay->addWidget(startButton);
	lay->addWidget(stopButton);
	lay->addWidget(logs);

	QWidget *window = new QWidget();
    	window->setLayout(lay);
	setCentralWidget(window);

	status = new QLabel("Zatrzymany");
	status->setFrameStyle( QFrame:: Panel | QFrame::Sunken );
	statusBar()->addWidget( status, 1);

	connect(startButton, SIGNAL(clicked()), this, SLOT(startServer()));
	connect(stopButton, SIGNAL(clicked()), this, SLOT(stopServer()));

	QRect screenGeometry = QApplication::desktop()->screenGeometry();
	int x = (screenGeometry.width()-this->width()) / 2;
	int y = (screenGeometry.height()-this->height()) / 2;
	move(x,y);

	connect(game, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));
	connect(game, SIGNAL(finished()), game, SLOT(deleteLater()));
	game->start();
}

Server::~Server()
{
	delete startButton;
	delete stopButton;
	delete status;
	delete port;
	delete logs;
	if(errorDialog!=NULL)
		delete errorDialog;
}

void Server::startServer()
{
	if(port->text()=="" || port->text().toInt()==0)
	{
		if(errorDialog!=NULL)
			delete errorDialog;
		errorDialog = new ErrorDialog("Proszę podać poprawny port", "Błędna konfiguracja");
		errorDialog->show();
		return;
	}
	game->getServer()->start(port->text().toInt());
	startButton->hide();
	stopButton->show();
	port->setDisabled(true);
	status->setText("Uruchomiony");
}

void Server::stopServer()
{
	game->getServer()->stop();
	stopButton->hide();
	startButton->show();
	port->setDisabled(false);
	status->setText("Zatrzymany");
}

void Server::handleResults(QString m)
{

}

void Server::closeEvent(QCloseEvent *event)
{
	game->close();game->quit();unisleep(500);
}

void Server::read(int id,QByteArray message)
{
	logs->append(QString::fromUtf8(message));
}
