#include <iostream>
#include "projeto.h"
#include <fstream>
#include <utility>
using namespace std;

unsigned int Commit::_lastC=0;


void sortCommits(vector<Commit> &commits);
Commit::Commit(Utilizador* user, int volume, int d, int m, int a): _userC(user){
	_idC=++_lastC;
    _volume = volume;
    _dataC.setData(d,m,a);
}

Commit::Commit(Utilizador *user, int volume, int d, int m, int a, int ID):_userC (user) {
	_idC=ID;
	_volume = volume;
	_dataC.setData(d,m,a);
	if(_lastC < _idC){
		_lastC = _idC;
	}
}

Utilizador* Commit::getUser () const{
	return _userC;
}

int Commit::getVolume () const{
	return _volume;
}

Data Commit::getData() const{
	return _dataC;
}


unsigned int Commit::getID() const{
	return _idC;
}

void Commit::setLastID(int id){
	_lastC = id;
}
//---------------------------------------------------------------------

void Branch::adicionaCommit(Commit cm){ 
	_commits.push_back(cm);
	sortCommits(_commits);
	if(cm.getUser()->getCargo()== "Junior")
		{
			dynamic_cast <Junior*>(cm.getUser())->setReputacao(dynamic_cast <Junior*>(cm.getUser())->getReputacao() + cm.getVolume() / 10);
		}
}
void Branch::addCommitVec(vector<Commit> vec)
{
	_commits.insert(_commits.begin(), vec.begin(), vec.end());
	sortCommits(_commits);
}
//---------------------------------------------------------------------
unsigned int Projeto::lastId = 0;

Projeto::Projeto(string nome,string tipo){
    _nome = nome;
	_tipo = tipo;
    _id = ++lastId;
    _clientNIF = 0;
}

string Projeto::getNome (){
	return _nome;
}

unsigned int Projeto::getId() const{
	return _id;
}

void Projeto::setID(int id){
	if(id == 0)
	{
	lastId--;
	}
	_id = id;
}

void Projeto::addCommit(Commit cm){
	_commits.push_back(cm);
	sortCommits(_commits);
	if(cm.getUser()->getCargo()== "Junior")
	{
		dynamic_cast <Junior*>(cm.getUser())->setReputacao(dynamic_cast <Junior*>(cm.getUser())->getReputacao() + cm.getVolume() / 10);
	}
	
}

void Projeto::addUtilizador (Utilizador * user){
	_ranking.push_back(user);
}

bool Projeto::existeUser(string nome){
	for(unsigned int i=0; i< _ranking.size();i++)
	{
		if(_ranking.at(i)->getNome()== nome)
			return true;
	}
	return false;
}
 void Projeto::removeUser(string nome){
	for(unsigned int i = 0; i <_ranking.size();i++)
	{
		if(_ranking.at(i)->getNome()== nome)
		{
			_ranking.erase(_ranking.begin()+i);
		}
	}
}
 void Projeto::removeAUsers(){
	for(unsigned int i = 0; i < _ranking.size(); i++)
		_ranking.at(i)->removeProjeto(_id);
}

void Projeto::imprimeUsers()
{
	cout << "Utilizadores do projeto com ID " << getId() << endl;
for (unsigned int i = 0; i < _ranking.size(); i++)
	{
		cout <<(i+1)<<"# "<< _ranking.at(i)->getNome()<<"     Cargo: "<<_ranking.at(i)->getCargo()<< endl;
	}
}

void Projeto::imprimeCoders()
{
	for (unsigned int i = 0; i < _ranking.size(); i++)
	{
		if (_ranking.at(i)->getCargo() == "Gestor")
			continue;
		cout << i + 1 << "# " << _ranking.at(i)->getNome() <<"  "<< _ranking.at(i)->getCargo() <<  endl;
	}
}

string Projeto::getChaveAcesso() const{
	return _chaveAcesso;
}

void Projeto::setChaveAcesso(string chave){
	_chaveAcesso = chave;
}

void Projeto::setLastID(int id){
	lastId = id;
}

int Projeto::getVolume(string nome_user, Data d1, Data d2) const {
	int volume = 0;
	for (unsigned int i = 0; i < _commits.size(); i++)
	{
		if (_commits.at(i).getUser()->getNome() == nome_user)
		{
			if (d1 == Data(0, 0, 0) && d2 == Data(0, 0, 0)) //n�o quer de um periodo especifico
			{
				volume += _commits.at(i).getVolume();
			}
			else if (_commits.at(i).getData() >= d1 && _commits.at(i).getData() <= d2)
			{
				volume += _commits.at(i).getVolume();
			}
		}
	}
	return volume;
}



int Projeto::getVolumeTotal(Data d1, Data d2) const
{
	int volume=0;
	for(unsigned int i = 0; i < _ranking.size();i++)
	{
		volume+= getVolume(_ranking.at(i)->getNome(),d1,d2);
	}
	return volume;
}

void Projeto::imprimeHistorico()
{
	for (unsigned int i = 0;i < _commits.size(); i++)
	{
		cout << "Commit: " << _commits.at(i).getID()
			<< " Autor: " << _commits.at(i).getUser()->getNome()
			<<" Branch: MASTER"
			<< " Data: " << _commits.at(i).getData().getDia()
						<< "/" << _commits.at(i).getData().getMes()
						<< "/" << _commits.at(i).getData().getAno()
			<<" Volume: "<< _commits.at(i).getVolume()<<endl;
	}
	   	 
}

float Projeto::getFreq(string user, Data d1, Data d2) const {
	float userCommit = 0, totalCommits = 0;
	for (unsigned int i = 0; i < _commits.size(); i++) {
		if (d1 == Data(0, 0, 0) && d2 == Data(0, 0, 0)) {
			totalCommits = _commits.size();
			if (_commits.at(i).getUser()->getNome() == user) {
				userCommit++;
			}
		}
		else if (_commits.at(i).getData() >= d1 && _commits.at(i).getData() <= d2) {
			totalCommits++;
			if (_commits.at(i).getUser()->getNome() == user) {
				userCommit++;
			}
		}
	}
	return userCommit / totalCommits;
}


void sortCommits(vector<Commit> &commits)//por data
{
	for (unsigned int j = commits.size() - 1; j > 0; j--)
	{
		bool troca = false;
		for (unsigned int i = 0; i < j; i++)
			if (commits[i + 1].getData() < commits[i].getData())
			{
				std::swap(commits[i], commits[i + 1]);
				troca = true;
			}
		if (!troca) break;
	}

}

vector <Commit> Projeto::filterCommits(vector<int> id) {
	vector <Commit> commits;
	for (unsigned int i = 0; i < _commits.size(); ++i) {
		for (unsigned int j = 0; j < id.size(); ++j) {
			if (_commits.at(i).getID() == (unsigned int) id.at(i)){
				commits.push_back(_commits.at(i));
			}
		}
	}
	return commits;
}

void Projeto::getInfo() const{
	Data d1(0,0,0);
	cout <<"#Nome:            "<< _nome << endl
		 <<"#ID:              "<< _id   << endl
		 <<"#Tipo de projeto: "<<_tipo  << endl
		 <<"#Chave de acesso: "<<_chaveAcesso << endl
		 <<"#Volume:          "<< getVolumeTotal(d1, d1) << endl;

}

void Projeto::setUsers(vector<Utilizador*> newU)
{
	_ranking = newU;
}

//---------------------------------------------------------------------

Avancado::Avancado(string nome): Projeto(nome,"Avancado"){}

void Avancado::addBranch(string nome)
{
	Branch* newbranch= new Branch(nome);
	for (unsigned int i = 0; i < _branches.size(); i++)
	{
		if (_branches.at(i)->getNome() == nome)
			throw BranchRepetido(nome);
	}
	_branches.push_back(newbranch);
	return;
}

void Avancado::addBranch_ref(Branch *branch) {
	_branches.push_back(branch);
}

void Avancado::removeBranch(string nome)
{
	for(unsigned int i =0; i < _branches.size(); i++)
	{
		if (_branches.at(i)->getNome() == nome)
		{
			_branches.erase(_branches.begin() + i);
			return;
		}
	}
	throw NoSuchBranch(nome);
}

void Avancado::merge(string nome)
{
	vector<Commit> v;
	for(unsigned int i = 0; i < _branches.size(); i++)
	{
		if (_branches.at(i)->getNome() == nome)
		{
			v = _branches.at(i)->getCommits();
			_commits.insert(_commits.begin(),v.begin(), v.end());
			sortCommits(_commits);
			_branches.erase(_branches.begin() + i);
			return;
		}
	}
	throw NoSuchBranch(nome);
}

void Avancado::merge(string nome1, string nome2)
{
	int n1=-1, n2=-1;
	for (unsigned int i = 0; i < _branches.size(); i++)
	{
		if (_branches.at(i)->getNome() == nome1)
		{
			n1 = i;
		}
		if (_branches.at(i)->getNome() == nome2)
		{
			n2 = i;
		}
	}
	if (n1 == -1){
		throw NoSuchBranch(nome1);
	}
	else if (n2 == -1){
		throw NoSuchBranch(nome2);
	}
	_branches.at(n1)->addCommitVec(_branches.at(n2)->getCommits());
	_branches.erase(_branches.begin() + n2);

}


void Avancado::imprimeBranches() {

	cout << "MASTER\n";
	for(unsigned int i = 0; i < _branches.size(); i++)
	{
		cout<<i+1<<"#  " << _branches.at(i)->getNome()<< endl;
	}
}

Branch* Avancado::existeBranch(string nome){
	for(unsigned int i = 0; i < _branches.size(); i++)
	{
		if(_branches.at(i)->getNome()== nome)
			return _branches.at(i);
	}
throw NoSuchBranch(nome);
}

void Avancado::imprimeHistorico()
{
	Projeto::imprimeHistorico();
	vector<Commit> com;

	for (unsigned int i = 0;i < _branches.size(); i++)
		{com= _branches.at(i)->getCommits();
		for(unsigned int j = 0; j < com.size();j++)
		{
			cout << "Commit: " << com.at(j).getID()
				<< " Autor: " << com.at(j).getUser()->getNome()
				<< " Branch: " << _branches.at(i)->getNome()
				<< " Data: " << com.at(j).getData().getDia()
							<< "/" << com.at(j).getData().getMes()
							<< "/" << com.at(j).getData().getAno()
				<<" Volume: "<< com.at(j).getVolume()<<endl;
		}
		}


}


int Avancado::getVolume(string nome_user,Data d1,Data d2) const
{
 int volume = Projeto::getVolume(nome_user,d1,d2);
 vector<Commit> commits;
 for(unsigned int j=0; j < _branches.size(); j++)
 {
commits= _branches.at(j)->getCommits();
	 for (unsigned int i = 0; i < commits.size(); i++)
		{
			if (commits.at(i).getUser()->getNome() == nome_user)
			{
				if (d1 == Data(0, 0, 0) && d2 == Data(0, 0, 0)) //n�o quer de um periodo especifico
				{
					volume += commits.at(i).getVolume();
				}
				else if (commits.at(i).getData() >= d1 && commits.at(i).getData() <= d2)
				{
					volume += commits.at(i).getVolume();
				}
			}
		}
 }




return volume;
}

int Avancado::getVolumeTotal(Data d1, Data d2) const
{
	int volume=0;
		for(unsigned int i = 0; i < _ranking.size();i++)
		{
			volume+= getVolume(_ranking.at(i)->getNome(),d1,d2);
		}

	return volume;
}

void Avancado::getInfo() const{ //Nao e chamada a funcao do projeto porque o volume e calculado de maneira diferente
	Data d1(0,0,0);
		cout <<"#Nome:            "<< _nome << endl
			 <<"#ID:              "<< _id   << endl
			 <<"#Tipo de projeto: "<<_tipo  << endl
			 <<"#Chave de acesso: "<<_chaveAcesso << endl
			 <<"#Volume:          "<< getVolumeTotal(d1, d1) << endl
			 <<"#Branches:        ";

		if(_branches.size()==0)
		{
			cout<<"/----/"<<endl;
			return;
		}
		for(unsigned int i =0; i < _branches.size(); i++)
		{
			cout << _branches.at(i)->getNome();
			if(i!=_branches.size()-1)
				cout<<"/ ";
			else
				cout<<endl;
		}

}

//-----------------------------------------------------------------------------

vector <Utilizador *> findUtilizadores(vector <int> id, vector <Utilizador *> users) {
	vector <Utilizador *> utilizadores;
	for (unsigned int i = 0; i < id.size(); i++)
	{
		for (unsigned int j = 0; j < users.size(); ++j) {
			if (users.at(i)->getNIF() == id.at(i))
			{
				utilizadores.push_back(users.at(i));
			}
		}
	}
	return utilizadores;
}



Utilizador* findUtilizador(int id, vector <Utilizador *> users) {
	string nome= "UtilizadorInvalido";
	for (unsigned int i = 0; i < users.size(); i++)
	{
		if (users.at(i)->getNIF() == id)
		{
			return users.at(i);
		}
	}
	throw NoSuchUser(nome);
}
vector<Commit> readCommits(vector <Utilizador *> users, string ficheiroC) {
	ifstream file;
	file.open(ficheiroC);
	Utilizador* user = new Utilizador();
	string ID, volume, userID, temp,test;
	int d, m, a, _id, _userID, _volume;
	char b;
	vector <Commit> commits;
	if (file.is_open()) {
		while (file.good()) {
			getline(file, ID);
			if(ID.empty())
			{
				continue;
			}
			_id = stoi(ID);
			getline(file, temp);
			while (1) {
				getline(file, userID);
				if (userID == "endU") break;
				_userID = stoi(userID);
			}
			getline(file, volume);
			_volume = stoi(volume);
			file >> d >> b >> m >> b >> a;
			getline(file, temp);
			getline(file, temp);
			try {
				 user = findUtilizador(_userID, users);
			} catch (NoSuchUser & e) {
				cout << "Erro na leitura do ficheiro dos commits.\n";
				exit(0);
			}

			Commit c = Commit(user,_volume,d,m,a,_id);

			commits.push_back(c);

		}
	}
	else {
		cout << "\n*Ficheiro de commits nao encontrado*\n" << endl;
		exit(0);
	}
	return commits;
}



//-----------------------------2 parte---------------------------------
//---------------------------------------------------------------------
unsigned Projeto::getClient() const{
	return _clientNIF;
}

void Projeto::setClient(unsigned cl_nif){
	_clientNIF = cl_nif;

}

//---------------------------------------------------------------------
ProjetoPtr::ProjetoPtr(Projeto* proj){
	projeto = proj;
}

Projeto* ProjetoPtr::getProjeto () const{
	return projeto;
}

string ProjetoPtr::getName() const{
	return projeto->getNome();
}

unsigned ProjetoPtr::getID() const{
	return projeto->getId();
}

unsigned ProjetoPtr::getClient() const{
	return projeto->getClient();
}

vector <Utilizador*> ProjetoPtr::getUsers() const{
	return projeto->getUsers();
}

void ProjetoPtr::setChaveAcesso(string chave){
	projeto->setChaveAcesso(chave);
}

