#include "empresa.h"
#include <fstream>

using namespace std;

int Empresa::novoProjeto() {
	string nome, tipo;
	Avancado* projA;
	Projeto* projB;
	cout << "Nome do Projeto? \n";
	cin >> nome;
	TIPO: cout << "Projeto Basico ou Avançado?(B/A)\n";
	cin >> tipo; // Como e que implemento uma exception se ele der uma string vazia?
	if (tipo == "B") {
		projB = new Projeto(nome, "Basico");
		_projetos.push_back(projB);
		cout << "Projeto " << nome << " criado com ID " << projB->getId()
				<< endl;
		return projB->getId();
	} else if (tipo == "A") {
		projA = new Avancado(nome);
		_projetos.push_back(projA);
		cout << "Projeto " << nome << " criado com ID " << projA->getId()
				<< endl;
		return projA->getId();
	} else {
		cout << "Opcao invalida! Tenta outra vez. \n\n";
		goto TIPO;
	}

}

void Empresa::removeProjeto(Projeto* proj) {
	removeObjeto<Projeto*>(_projetos, proj);
}
/*
 void Empresa::removeProjeto(Projeto * projetoARemover){
 for(unsigned int i = 0; i < _projetos.size(); i++)
 {
 if(_projetos.at(i) == projetoARemover)
 {
 cout << "Projeto " << projetoARemover->getNome() <<" removido. \n";
 _projetos.erase(_projetos.begin() + i);
 return;
 }
 }
 }
 */

void Empresa::novoUtilizador() {

	Gestor* gestor;
	Senior* senior;
	Junior* junior;
	string nome, email, status;
	int d, m, a, NIF, reput;

	cout << "Nome do Utilizador: ";
	cin >> nome;

	try {
		existeUser(nome);
	} catch (UserRepetido &e) {
		cout << e.getName() << " j� existe. Introduza outro nome.\n\n";
		novoUtilizador();
	}

	cout << "Data de Nascimento(d/m/a): ";
	cin >> d >> m >> a; //VERIFICACAO
	cout << "Email: ";
	cin >> email;
	cout << "Digite NIF: ";
	cin >> NIF;

	try {
		existeNIF(NIF);
	} catch (NIFRepetido &e) {
		cout << e.getNIF()
				<< " j� existe. Introduza um utilizador com um NIF diferente.\n\n";
		novoUtilizador();
	}

	cout << "Tipo(Gestor(G)/Programador(S/J)): ";
	cin >> status;
	if (status == "G") {
		gestor = new Gestor(nome, d, m, a, email, 2500, NIF, "Gestor");
		cout << "\nGestor criado!\n";
		_utilizadores.push_back(gestor);
	} else if (status == "S") {

		senior = new Senior(nome, d, m, a, email, 1000, NIF, "Senior");
		cout << "\nSenior criado!\n";
		_utilizadores.push_back(senior);

	} else if (status == "J") {
		cout << "Reputacao: ";
		cin >> reput;
		junior = new Junior(nome, d, m, a, email, reput, NIF, "Junior");
		cout << "\nJunior criado!\n";
		_utilizadores.push_back(junior);
	}

}

bool Empresa::removeUtilizador(Utilizador * utilizador) {
	return removeObjeto<Utilizador*>(_utilizadores, utilizador);
}

void Empresa::imprimeSalarios() {
	/*
	 if(_utilizadores.size() == 0)
	 {cout << "Nao existem utilizadores.\n";
	 return;}*/
	float Soma = 0;
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		cout << "Nome: " << _utilizadores.at(i)->getNome() << " Cargo: "
				<< _utilizadores.at(i)->getCargo() << " Salario: "
				<< _utilizadores.at(i)->getSalario() << endl;
		Soma += _utilizadores.at(i)->getSalario();
	}
	cout << "Soma total dos salarios: " << Soma << endl;
}

Utilizador* Empresa::existeUser(string nome) {
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		if (_utilizadores.at(i)->getNome() == nome) {
			return _utilizadores.at(i);

		}
	}
	throw(NoSuchUser(nome));
}
void Empresa::repeteUser(string nome) {
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		if (_utilizadores.at(i)->getNome() == nome) {
			throw(UserRepetido(nome));

		}
	}
	return;
}

void Empresa::existeNIF(int nif) {
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		if (_utilizadores.at(i)->getNIF() == nif) {
			throw NIFRepetido(nif);

		}
	}
	return;
}

Projeto* Empresa::editProj(int id) {
	for (unsigned int i = 0; i < getProjetos().size(); i++) {
		if (getProjetos().at(i)->getId() == (unsigned int) id)
			return getProjetos().at(i);
	}
	throw(NoSuchProject((unsigned int) id));
}

int Empresa::getVolume(string nome, Data d1, Data d2) const {
	int volume = 0;
	for (unsigned int i = 0; i < _projetos.size(); i++) {
		volume += _projetos.at(i)->getVolume(nome, d1, d2);
	}
	return volume;
}

float Empresa::getFreq(string nome, Data d1, Data d2) const {
	float freq = 0;
	for (unsigned int i = 0; i < _projetos.size(); i++) {
		freq += _projetos.at(i)->getFreq(nome, d1, d2);
	}
	return freq;
}

void Empresa::imprimeUser() {
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		cout << i + 1 << "# " << _utilizadores.at(i)->getNome()
				<< "     Cargo: " << _utilizadores.at(i)->getCargo() << endl;
	}
}

void Empresa::imprimeCoders() {
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		if (_utilizadores.at(i)->getCargo() == "Gestor")
			continue;
		cout << i + 1 << "# " << _utilizadores.at(i)->getNome()
				<< "     Cargo: " << _utilizadores.at(i)->getCargo() << endl;
	}
}

void Empresa::imprimeProjetos() {
	for (unsigned int i = 0; i < _projetos.size(); i++) {
		cout << _projetos.at(i)->getNome() << " ID: "
				<< _projetos.at(i)->getId() << endl;
	}
}

void Empresa::readUsers() {
	Utilizador* _gestor;
	Utilizador* _junior;
	Utilizador* _senior;

	ifstream file;
	file.open("utilizadores.txt");
	string nome, rank, email, data, n, ids, reputacao, money;
	char /*ch,*/b;
	int d, m, a, /*id,*/nif, rep;
	float salario;
	vector<int> dataV;
	vector<int> projId;

	if (file.is_open()) {
		while (file.good()) {
			getline(file, nome);
			cout << nome << endl;
			getline(file, rank);
			cout << rank << endl;
			if (rank == "J") {
				getline(file, reputacao);
				rep = stoi(reputacao);
			}
			file >> d >> b >> m >> b >> a;
			cout << d << b << m << b << a << endl;
			getline(file, n);
			cout << n;
			getline(file, email);
			cout << email << endl;
			projId.clear();
			while (1) {
				getline(file, ids);
				if (ids == "end")
					break;
				int id = stoi(ids);
				projId.push_back(id);
			}
			for (unsigned int i = 0; i < projId.size(); ++i) {
				cout << projId.at(i) << endl;
			}
			file >> nif;
			cout << "NIF " << nif << endl;
			getline(file, n);
			cout << n;
			if (rank != "J") {
				getline(file, money);
				salario = stof(money);
			}
			getline(file, n);
			cout << n;

			if (rank == "G") {
				_gestor = new Gestor(nome, d, m, a, email, salario, nif,
						"Gestor");
				for (unsigned int i = 0; i < projId.size(); ++i) {
					_gestor->addProjeto(projId.at(i));
				}
				_utilizadores.push_back(_gestor);
			}
			if (rank == "S") {
				_senior = new Senior(nome, d, m, a, email, salario, nif,
						"Senior");
				for (unsigned int i = 0; i < projId.size(); ++i) {
					_senior->addProjeto(projId.at(i));
				}
				_utilizadores.push_back(_senior);
			}

			if (rank == "J") {
				_junior = new Junior(nome, d, m, a, email, rep, nif, "Junior");
				dynamic_cast <Junior*>(_junior)->setSalario();
				for (unsigned int i = 0; i < projId.size(); ++i) {
					_junior->addProjeto(projId.at(i));
				}
				_utilizadores.push_back(_junior);
			}

		}
		file.close();

	} else {
		cout << "File not found" << endl;
	}
}

void Empresa::readProjetos() {
	ifstream file;
	file.open("projetos.txt");
	string tipo, nome, pass, temp;
	vector<int> usersID;
	vector<int> commitID;
	if (file.is_open()) {
		while (file.good()) {
			getline(file, tipo);
			cout << tipo << endl;
			getline(file, nome);
			cout << nome << endl;
			getline(file, pass);
			cout << pass << endl;
			getline(file, temp);
			cout << temp << endl;
			while (1) { //ciclo para ler os usersID de um projeto
				getline(file, temp);
				if (temp == "endU")
					break;
				int id = stoi(temp);
				usersID.push_back(id);
			}
			for (size_t i = 0; i < usersID.size(); ++i) {
				cout << usersID.at(i) << endl;
			}
			getline(file, temp);
			cout << temp << endl;
			getline(file, temp);
			while (1) { //ciclo para ler os ID dos commits de um projeto
				getline(file, temp);
				if (temp == "endC")
					break;
				int id = stoi(temp);
				usersID.push_back(id);
			}
		}
	}
}

void Empresa::writeUsers() {
	ofstream file;
	file.open("utilizadores01.txt");
	string cargo;
	for (unsigned int i = 0; i < _utilizadores.size(); i++) {
		file << _utilizadores.at(i)->getNome() << endl;
		file << _utilizadores.at(i)->getCargo().at(0) << endl;
		if (_utilizadores.at(i)->getCargo() == "Junior") {
			file << dynamic_cast <Junior*>(_utilizadores.at(i))->getReputacao() << endl;
		}
		file << _utilizadores.at(i)->getDataNascimento().getDia() << "/"
				<< _utilizadores.at(i)->getDataNascimento().getMes() << "/"
				<< _utilizadores.at(i)->getDataNascimento().getAno() << endl;
		file << _utilizadores.at(i)->getEmail() << endl;
		vector<int> ids = _utilizadores.at(i)->getProjetos();
		if (ids.size() != 0) {
			for (unsigned int j = 0; j < ids.size(); j++) {
				file << ids.at(j) << endl;
			}
		}
		file << "end" << endl;
		file << _utilizadores.at(i)->getNIF() << endl;
		if (_utilizadores.at(i)->getCargo() != "Junior") {
			file << _utilizadores.at(i)->getSalario() << endl << endl;
		}
	}
	file.close();

}

void Empresa::converteJunior(Utilizador * junior) {

	if (dynamic_cast <Junior*> (junior)->getReputacao() > 9999) {
		string nome = junior->getNome();
		int dia = junior->getDataNascimento().getDia();
		int mes = junior->getDataNascimento().getMes();
		int ano = junior->getDataNascimento().getAno();
		int NIF = junior->getNIF();
		string email = junior->getEmail();
		Utilizador* novoSenior = new Senior(nome, dia, mes, ano, email, 1000,
				NIF, "Senior"); // Utilizador ou Senior?
		removeUtilizador(junior);
		getUsers().push_back(novoSenior);

	}
}

/*Avancado* Empresa::converteBasico(Projeto * proj) {
 Avancado* novoAvancado;
 string nome = proj->getNome();
 vector<Commit> commits = proj->getCommits();
 unsigned int id = proj->getId();
 vector<Utilizador *> ranking = proj->getUsers();
 string chaveAcesso = proj->getChaveAcesso();
 proj->alteraID(-1);
 novoAvancado = new Avancado(nome);

 for (unsigned int i = 0; i < ranking.size(); i++)
 novoAvancado->addUtilizador(ranking.at(i));

 for (unsigned int i = 0; i < commits.size(); i++)
 novoAvancado->addCommit(commits.at(i));

 novoAvancado->setID(id);

 novoAvancado->setChaveAcesso(chaveAcesso);

 for (unsigned int i = 0; i < _projetos.size(); i++)
 {
 if(_projetos.at(i)->getId() == proj->getId())
 {
 _projetos.erase(_projetos.begin() + i);
 }
 }

 _projetos.push_back(novoAvancado);


 }*/
