#ifndef utilizador
#define utilizador

#include <iostream>
#include <string>
#include <vector>
#include "projeto.h"

/*TO DO LIST:

-construtores
-getters
-Adicionar/apagar/modificar objetos
*/

using namespace std;

class Data {
	int dia, mes, ano;
public:
	Data();
	void setData(int d, int m, int a);
};

class Utilizador
{
protected:
	string _nome;
	Data dataNascimento;
	string _email;

public:
	Utilizador(string nome, int d, int m, int a,string email);
};

class Coder: public Utilizador
{
private:
	float _reputacao;
	vector<Projeto *> _projetos;
	float _salario;

public:
	Coder(string nome, int d, int m, int a,string email, float salario, float reputacao);

};



class Gestor: public Utilizador
{
	vector<Projeto *> _projetos;

public:
	Gestor(string nome, int d, int m, int a,string email);
};

class Senior:  public Utilizador,  public Coder
{
	int _NIF;
public:
	Senior(string nome, int d, int m, int a,string email,float salario, float reputacao, int NIF);
};

class Junior : public Utilizador, public Coder {
public:
	Junior(string nome, int d, int m, int a,string email,float salario, float reputacao, int NIF);

};






#endif // !utilizador

