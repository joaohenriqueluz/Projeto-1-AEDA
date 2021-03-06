#ifndef PROJ_AEDA_EMPRESA_H
#define PROJ_AEDA_EMPRESA_H

#include <vector>
#include <string>
#include <list>
#include <queue>
#include <unordered_set>
#include "projeto.h"
#include "client.h"
#include "BST.h"
#include "ticket.h"


using namespace std;

/**
 * @brief Struct com o apontador de um projeto
 */
struct  ProjetoPtrHash
{
	/**
	 * @brief Devolve o indice do projeto na tabela de dispersao
	 * @param proj - projeto a ser colocado
	 * @return indice
	 */
	unsigned int operator() (const ProjetoPtr& proj) const
	{
		return proj.getID()*2654435761 % (2^32);
	}

	/**
	 * @brief Compara dois projetos
	 * @param proj1 - projeto a ser comparado
	 * @param proj2 - projeto a ser comparado
	 * @return Verdadeiro se os projetos tiverem o mesmo ID, senao devolve falso
	 */
	bool operator() (const ProjetoPtr& proj1, const ProjetoPtr& proj2) const
	{
		return proj1.getID() == proj2.getID();
	}
};

typedef unordered_set<ProjetoPtr, ProjetoPtrHash, ProjetoPtrHash> HashTabProjetos;


/**
 * @brief Classe da empresa
 * @param _projetos - projetos da empresa
 * @param _utilizadores - utilizadores da empresa
 * @param _clients - clientes da empresa
 * @param _pasteProjects - projetos da empresa terminados
 * @param _tickets - tickets dos projetos em desenvolvimento
 */
class Empresa {
	vector<Projeto *> _projetos;
	vector<Utilizador *> _utilizadores;
	BST<Client> _clients;
	HashTabProjetos _pastProjects;
	priority_queue<Ticket> _tickets;
public:

	/**
	 * @brief Construtor da classe empresa
	 */
	Empresa():_clients(Client("","",0,0)){};

	/**
	 * @brief Adiciona um novo utilizador a empresa
	 */
	void novoUtilizador();

	/**
	 * @brief Remove o utilizador identificado pelo nome fornecido
	 * @param nome - nome do utilizador
	 * @return verdadeiro se o utilizador e removido com sucesso
	 */
	bool removeUtilizador(string nome);

	/**
	 * @brief Adiciona um novo projeto a empresa
	 * @return id do projeto criado
	 */
	int novoProjeto();

	/**
	 * @brief Remove o projeto fornecido da empresa
	 * @param proj - projeto a remover
	 */
	void removeProjeto(Projeto * proj);

	/**
	 * @brief Adiciona o projeto fornecido a empresa
	 * @param proj - projeto a adicionar
	 */
	void addProject (Projeto* proj);

	/**
	 * @brief Imprime no ecra os utilizadores, os respetivos cargos e salarios e o total de todos os salarios
	 */
	void imprimeSalarios();

	/**
	 * @brief Retorna o utilizador identificado pelo nome fornecido
	 * @param nome - nome do utilizador
	 * @return utilizador
	 */
	Utilizador* existeUser(string nome);

	/**
	 * @brief Retorna utilizador com o NIF passado por argumento
	 * @param nif - NIF do utilizador procurado
	 * @return utilizador
	 */
	Utilizador* existeUserID(int nif);

	/**
	 * @brief Lanca excecao se nao existir na empresa nenhum utilizador com o NIF fornecido
	 * @param nif - NIF do utilizador
	 */
	void existeNIF(int nif);


	/**
	 * @brief Verifica se ja existe esse email, lancando uma excecao se for verdade
	 * @param email - email para verificar se e repetido ou nao
	 */
	void existeEmail(string email);

	/**
	 * @brief Verifica se o utilizador com nome fornecido ja existe, lancando exececao se nao existir nenhum com esse nome
	 * @param nome - nome do utilizador a verigicar se ja existe ou nao
	 */
	void repeteUser(string nome);

	/**
	 * @brief Devolve endereco do projeto com id dado, lancando uma excecao no caso de nao existir ou de o utilizador nao pertencer a esse projeto
	 * @param id - ID do projeto a ser retornado
	 * @return apontador para Projeto com ID pedido
	 */
	Projeto * editProj(int id);

	/**
	 * @brief Retorna o volume total das contribuicoes do utilizador ,identificado pelo nome fornecido, feitas entre duas datas
	 * @param nome - nome do utilizador
	 * @param d1 - primeira data
	 * @param d2 - segunda data
	 * @return volume
	 */
	int getVolume(string nome, Data d1, Data d2) const;

	/**
	 * @brief Retorna a frequencia de commits feitos  em todos os projetos pelo utilizador, identificado pelo nome fornecido, entre duas datas
	 * @param nome - nome do utilizador
	 * @param d1 - primeira data
	 * @param d2 - primeira data
	 * @return frequencia
	 */
	float getFreq(string nome, Data d1, Data d2) const;

	/**
	 * @brief Retorna os projetos da empresa
	 * @return projetos
	 */
	vector<Projeto *> getProjetos() const { return _projetos; }

	/**
	 * @brief Retorna os utilizadores da empresa
	 * @return utilizadores
	 */
	vector<Utilizador*>&  getUsers() { return _utilizadores; }

	/**
	 * @brief Imprime, no ecra, todos os utilizadores da empresa
	 */
	void imprimeUser();

	/**
	 * @brief Imprime, no ecra, todos os utilizadores juniores e seniores da empresa
	 */
	void imprimeCoders();

	/**
	 * @brief Imprime, no ecra, todos os projetos da empresa
	 */
	void imprimeProjetos();

	/**
	 * @brief Retira informacao sobre os utilizadores da empresa a partir de um ficheiro
	 * @param ficheiro - ficheiro lido
	 */
	void readUsers(string ficheiro);

	/**
	 * @brief Retira informacao sobre os tickets dos projetos da empresa a partir de um ficheiro
	 * @param ficheiro - ficheiro lido
	 */
	void readTickets(string ficheiro);

	/**
	 * @brief Retira informacao sobre os clientes da empresa a partir de um ficheiro
	 * @param ficheiro - ficheiro lido
	 */
	void readclients(string ficheiro);

	/**
	 * @brief Regista utilizadores num ficheiro de texto
	 * @param ficheiro - ficheiro escrito
	 */
	void writeUsers(string ficheiro);

	/**
	 * @brief Regista tickets num ficheiro de texto
	 * @param ficheiro - ficheiro escrito
	 */
	void writeTickets(string ficheiro);

	/**
	 * @brief Regista projetos num ficheiro de texto
	 * @param ficheiro - ficheiro escrito
	 */
	void writeProjetos(string ficheiro);

	/**
	 * @brief Regista clientes num ficheiro de texto
	 * @param ficheiro - ficheiro escrito
	 */
	void writeClients(string ficheiro);

	/**
	 * @brief Regista commits num ficheiro de texto
	 * @param ficheiro - ficheiro escrito
	 */
	void writeCommits(string ficheiro);

	/**
	 * @brief Retira informacao sobre os projetos da empresa a partir de um ficheiro
	 * @param ficheiroP - ficheiro de projetos
	 * @param ficheiroC - ficheiro de commits
	 */
	void readProjetos(string ficheiroP, string ficheiroC);

	/**
	 * @brief Converte um utilizador junior em senior
	 * @param junior - junior a ser convertido
	 * @return verdadeiro se nao conseguir realizar a conversao, caso contrario retorna falso
	 */
	bool converteJunior(Utilizador* junior);

	/**
	 * @brief Encontra o projeto com o maior id e atribui esse valor a variavel lastId
	 */
	void setProjLastID();

	/**
	 * @brief Adiciona cliente a arvore binaria com os clientes da empresa
	 * @param c - cliente a adicionar a empresa
	 */
	void addClient(Client c);

	/**
	 * @brief Remove cliente da arvore binaria com os clientes da empresa
	 * @param c - cliente a remover da empresa
	 */
	void removeClient(Client c);

	/**
	 * @brief Procura cliente fornecido e devolve os projetos encomendados por este
	 * @param c - cliente
	 * @return projetos encomendados pelo cliente
	 */
	vector<Projeto*> getProjectsOfClient(Client c);

	/**
	 * @brief Procura cliente com nif fornecido
	 * @param nif - nif do cliente
	 * @return cliente
	 */
	Client getClient (unsigned nif);

	/**
	 * @brief Adiciona projeto ao cliente com nif fornecido
	 * @param nif - nif do cliente
	 * @param proj - projeto a adicionar ao cliente
	 */
	void addProjectToClient (unsigned nif, Projeto * proj);

	/**
	 * @brief Remove projeto do cliente com nif fornecido
	 * @param nif - nif do cliente
	 * @param id_proj - id do projeto a remover do cliente
	 */
	void removeProjectFromClient (unsigned nif, unsigned int id_proj);

	/**
	 * @brief Alterar numero do contacto do cliente com nif fornecido
	 * @param nif - nif do cliente
	 * @param novo_num - novo numero de contacto
	 * @return verdadeiro se encontrou o cliente, caso contrario falso
	 */
	bool modifyContacto (unsigned nif, unsigned novo_num);

	/**
	 * @brief Altera chave de acesso do projeto terminado
	 * @param proj - projeto
	 * @param novaChave - nova chave de acesso
	 */
	void alterarChavePastProj (Projeto* proj, string novaChave);

	/**
	 * @brief Altera nome do projeto terminado
	 * @param proj - projeto a ser alterado
	 * @param novoNome - novo nome do projeto
	 */
	void alterarNomePastProj (Projeto* proj, string novoNome);

	/**
	 * @brief Coloca projeto na tabela de dispersao dos projetos terminados, removendo-o dos projetos em desenvolvimento
	 * @param id - id do projeto em desenvolvimento a passar a projeto terminado
	 */
	void toPastProject (unsigned int id);

	/**
	 * @brief Coloca projeto no vetor de projetos em desenvolvimento, removendo-o dos projetos terminados
	 * @param id - id do projeto terminado a ser reativado
	 */
	void toWorkingProject (unsigned int id);

	/**
	 * @brief Adiciona projeto a tabela de dispersao dos projetos terminados
	 * @param proj - projeto a ser adicionado aos projetos terminados
	 */
	void addPastProject (Projeto* proj);

	/**
	 * @brief Remove projeto da tabela de dispersao dos projetos terminados, lancando excecao se nao existir nenhum projeto com o id fornecido
	 * @param id - id do projeto a ser removido dos projetos terminados
	 * @return Verdadeiro se o projeto existir, senao devolve falso
	 */
	bool removePastProject (unsigned int id);

	/**
	 * @brief Procura o projeto terminado com id fornecido, lancando excecao se nao o encontrar
	 * @param id - id do projeto a procurar
	 * @return projeto terminado com id fornecido
	 */
	Projeto* getPastProject (unsigned int id);

	/**
	 * @brief Procura os projetos terminados nos quais o utilizador com NIF fornecido participou
	 * @param NIF - NIF do utilizador
	 * @return lista dos projetos terminados
	 */
	list<Projeto*> pastProjectsWithUser (int NIF);

	/**
	 * @brief Procura os projetos terminados os quais o cliente com NIF fornecido encomendou
	 * @param NIF - NIF do cliente
	 * @return lista dos projetos terminados
	 */
	list<Projeto*> pastProjectsWithClient(unsigned int NIF);

	/**
	 * @brief Retorna o projeto mais urgente
	 * @return projeto
	 */
	Projeto* getMostUrgent();

	/**
	 * @brief Retorna o id do proximo proximo projeto com ticket exequivel para o utilizador fornecido
	 * @param user - utilizador a saber proximo projeto a realizar
	 * @return id do projeto a realizar a seguir
	 */
	int getNextTicket(Utilizador* user);

	/**
	 * @brief Remove o ticket correspondente ao projeto fornecido
	 * @param P - Projeto associado ao ticket a ser removido
	 * @return verdaderio se a operacao � efetuada com sucesso, senao retorna falso
	 */
	bool removeTicket(Projeto* P);

	/**
	 * @brief Imprime todos os clientes e o numero de projetos encomendados por ordem descrecente;
	 */
	void printClientNumProj();

	/**
	 * @brief Imprime todos os projetos emcomendados pelo cliente identificado pelo NIF fornecido
	 * @param NIF - NIF do cliente
	 */
	void printClientProj(unsigned NIF);

	/**
	 * @brief Atualiza o projeto atual dos utilizadores do projeto identificado pelo id fornecido
	 * @param id - ID do projeto
	 */
	void updateCurretProj(int id);

	/**
	 * @brief Imprime todos os projetos terminados, presentes na tabela de dispersao
	 */
	void printPastproj();

	/**
	 * @brief Verifica se existe um projeto terminado com o id fornecido;
	 * @param id - id do projeto procurado
	 * @return Verdadeiro se existir projeto com o id dado, senao retorna falso;
	 */
	bool existePastProj(int id);

	/**
	 * @brief Adiciona novo ticket a fila de prioridade
	 * @param t - novo ticket a adicionar
	 */
	void addTicket(Ticket t);

	/**
	 * @brief Apaga o Utilizador com o NIF dado dos projetos concluidos
	 * @param NIF - NIF do Utilizador
	 */
	void removeUserFromPastProj(int NIF);

	/**
	 * @brief Apaga o Cliente com o NIF dado dos projetos concluidos
	 * @param NIF - NIF do Cliente
	 */
	void removeClientFromPastProj(unsigned int NIF);

	/**
	 * @brief Apaga o Cliente com o NIF dado dos projetos em desenvolvimento
	 * @param NIF - NIF do Cliente
	 */
	void removeClientEmp(unsigned int NIF);

	/**
	 * @brief Desassocia o gestor do projeto identificado por id
	 * @param user - Gestor
	 * @param id - ID do projeto
	 */
	void removeProjFromGest(Utilizador* user, unsigned int id);

	/**
	 * @brief Imprime todos os projetos presentes na lista fornecida como argumento
	 * @param list - lista de projetos a ser impressos
	 */
	void printPPClient(list<Projeto*> list);

	/**
	 * @brief Devolve uma do ticket associado ao projeto fornecido
	 * @param proj - projeto
	 * @return Ticket do projeto
	 */
	Ticket getTicket(Projeto* proj);


};

/**
 * @brief Template para remover um objeto de um vetor
 * @param V - vetor do qual o objeto vai ser removido
 * @param objeto - objeto a remover
 * @return verdadeiro se encontrou objeto no vetor e o eliminou, senao retorna falso
 */
template<class T>
bool removeObjeto(vector<T> & V, T objeto){
	for(unsigned int i = 0; i < V.size(); i++)
			if(V.at(i)== objeto)
			{
				V.erase(V.begin()+i);
				return true;
			}
	return false;
}


#endif //PROJ_AEDA_EMPRESA_H
