/********************************************************
* FILENAME : Voo.cpp
* DESCRIPTION : Implementação de cadastro, salvamento, 
*               carregamento e listagem de voos.
* PUBLIC FUNCTIONS :
*   void Voo::cadastroVoo()        - Realiza o cadastro de um novo voo.
*   void Voo::listarVoo()          - Lista todos os voos cadastrados.
*   void Voo::salvarVoos()         - Salva os voos em arquivo binário.
*   void Voo::carregarVoos()       - Carrega os voos de um arquivo binário.
*
* NOTES :
* Essas funções fazem parte de um sistema de cadastro e listagem de voos.
* O código realiza o armazenamento e a leitura de informações dos voos 
* em um arquivo binário, além de realizar o cadastro e a listagem de voos.
*
* AUTHOR : Eric
* START DATE : 26 Nov 24
********************************************************/


#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <limits>
#include "Tripulacao.h"
#include "Voo.h"

using namespace std;

#define MAX_VOOS 100

vector<Voo> voos;
extern vector<Tripulacao> tripulacaoVet;

int contagemVoo = 0;

/********************************************************
* NAME : void Voo::salvarVoos()
* DESCRIPTION : Salva os voos cadastrados em um arquivo binário.
* INPUTS :
* PARAMETERS : 
* RETURN :
* Type : void
* Error code :
* Values : Nenhum
*******************************************************/
void Voo::salvarVoos()
{
    ofstream arquivo("voos.dat", ios::binary);

    if (arquivo.is_open())
    {

        for (int i = 0; i < contagemVoo; i++)
        {

            arquivo.write(reinterpret_cast<char *>(&voos[i].codigoVoo), sizeof(voos[i].codigoVoo));
            arquivo.write(reinterpret_cast<char *>(&voos[i].codigoAviao), sizeof(voos[i].codigoAviao));
            arquivo.write(voos[i].origem.c_str(), voos[i].origem.size() + 1);
            arquivo.write(voos[i].destino.c_str(), voos[i].destino.size() + 1);
            arquivo.write(reinterpret_cast<char *>(&voos[i].dia), sizeof(voos[i].dia));
            arquivo.write(reinterpret_cast<char *>(&voos[i].mes), sizeof(voos[i].mes));
            arquivo.write(reinterpret_cast<char *>(&voos[i].ano), sizeof(voos[i].ano));
            arquivo.write(reinterpret_cast<char *>(&voos[i].hora), sizeof(voos[i].hora));
            arquivo.write(reinterpret_cast<char *>(&voos[i].minuto), sizeof(voos[i].minuto));
            arquivo.write(reinterpret_cast<char *>(&voos[i].tarifa), sizeof(voos[i].tarifa));
            arquivo.write(voos[i].status.c_str(), voos[i].status.size() + 1);

            int codigoTripulacao = voos[i].getCodigoVoo(); // Exemplo: se tiver um código associado
            arquivo.write(reinterpret_cast<char *>(&codigoTripulacao), sizeof(codigoTripulacao));
            bool tripulacaoEmUso = tripulacaoVet[codigoTripulacao - 1].getTripulacaoEmUso();
            arquivo.write(reinterpret_cast<char *>(&tripulacaoEmUso), sizeof(tripulacaoEmUso));
        }
        arquivo.close();
    }

}

/********************************************************
* NAME : void Voo::carregarVoos()
* DESCRIPTION : Carrega os voos a partir de um arquivo binário.
* INPUTS :
* PARAMETERS : 
* RETURN :
* Type : void
* Error code :
* Values : Nenhum
*******************************************************/
void Voo::carregarVoos()
{
    ifstream arquivo("voos.dat", ios::binary);

    if (arquivo.is_open())
    {
        while (arquivo.read(reinterpret_cast<char *>(&codigoVoo), sizeof(codigoVoo)))
        {
            arquivo.read(reinterpret_cast<char *>(&codigoAviao), sizeof(codigoAviao));
            getline(arquivo, origem, '\0');
            getline(arquivo, destino, '\0');
            arquivo.read(reinterpret_cast<char *>(&dia), sizeof(dia));
            arquivo.read(reinterpret_cast<char *>(&mes), sizeof(mes));
            arquivo.read(reinterpret_cast<char *>(&ano), sizeof(ano));
            arquivo.read(reinterpret_cast<char *>(&hora), sizeof(hora));
            arquivo.read(reinterpret_cast<char *>(&minuto), sizeof(minuto));
            arquivo.read(reinterpret_cast<char *>(&tarifa), sizeof(tarifa));
            getline(arquivo, status, '\0');

            int codigoTripulacao;
            arquivo.read(reinterpret_cast<char *>(&codigoTripulacao), sizeof(codigoTripulacao));

            bool tripulacaoEmUso;
            arquivo.read(reinterpret_cast<char *>(&tripulacaoEmUso), sizeof(tripulacaoEmUso));

            Voo novoVoo;
            novoVoo.setCodigoVoo(codigoVoo);
            novoVoo.setCodigoAviao(codigoAviao);
            novoVoo.setOrigem(origem);
            novoVoo.setDestino(destino);
            novoVoo.setDia(dia);
            novoVoo.setMes(mes);
            novoVoo.setAno(ano);
            novoVoo.setHora(hora);
            novoVoo.setMinuto(minuto);
            novoVoo.setTarifa(tarifa);
            novoVoo.setStatus(status == "Ativo" ? 1 : 2);

            tripulacaoVet[codigoTripulacao - 1].setTripulacaoEmUso(tripulacaoEmUso);

            voos.push_back(novoVoo);
            contagemVoo++;
        }
        arquivo.close();
    }
}

int Voo::getCodigoAviao()
{
    return codigoAviao;
}

int Voo::getCodigoVoo()
{
    return codigoVoo;
}

int Voo::getTarifa()
{
    return tarifa;
}

int Voo::getDia()
{
    return dia;
}

int Voo::getMes()
{
    return mes;
}

int Voo::getAno()
{
    return ano;
}

int Voo::getHora()
{
    return hora;
}

int Voo::getMinuto()
{
    return minuto;
}

string Voo::getOrigem()
{
    return origem;
}

string Voo::getStatus(){
    return status;
}

string Voo::getDestino()
{
    return destino;
}

bool Tripulacao::getTripulacaoEmUso(){
    return tripulacaoEmUso;
}

vector<Tripulacao>& Tripulacao::getTripulantes() {
    return tripulantes;
}

void Voo::setCodigoAviao(int codigoAviao)
{
    this->codigoAviao = codigoAviao;
}

void Voo::setCodigoVoo(int codigoVoo)
{
    this->codigoVoo = codigoVoo;
}

void Voo::setTarifa(int tarifa)
{
    this->tarifa = tarifa;
}

void Tripulacao::setTripulacaoEmUso(bool tripualacaoEmUso){
    this->tripulacaoEmUso = tripualacaoEmUso;

} 

void Voo::setStatus(int status){
    switch (status)
    {
    case 1:
        this->status = "Ativo";
        break;

    case 2:
        this->status = "Inativo";
        break;

    }
}

void Voo::setDia(int dia)
{
    if (dia > 0 && dia <= 31)
    {
        this->dia = dia;
    }
    else
    {
        cout << "Dia inválido. Deve ser cadastrado um dia entre 1 e 31." << endl;
    }
}

void Voo::setMes(int mes)
{
    if (mes > 0 && mes <= 12)
    {
        this->mes = mes;
    }
    else
    {
        cout << "Mês inválido. Deve ser cadastrado um mês entre 1 e 12." << endl;
    }
}

void Voo::setAno(int ano)
{
    if (ano >= 2024 && ano <= 2030)
    {
        this->ano = ano;
    }
    else
    {
        cout << "Deve ser cadastrado voos entre 2024 e 2030" << endl;
    }
}

void Voo::setHora(int hora)
{
    if (hora >= 0 && hora <= 23)
    {
        this->hora = hora;
    }
    else
    {
        cout << "Hora invalida" << endl;
    }
}

void Voo::setMinuto(int minuto)
{
    if (minuto >= 0 && minuto <= 59)
    {
        this->minuto = minuto;
    }
    else
    {
        cout << "Minuto invalido" << endl;
    }
}

void Voo::setOrigem(string origem)
{
    this->origem = origem;
}

void Voo::setDestino(string destino)
{
    this->destino = destino;
}


/****************************************************************************
* NAME : void Voo::cadastroVoo()
* DESCRIPTION : Realiza o cadastro de um novo voo.
* INPUTS : string origem - Origem do voo
*          string destino - Destino do voo
*          int codigoAviao - Código do avião
*          int tarifa - Valor da tarifa do voo
*          int status - Status do voo (1 para Ativo, 2 para Inativo)
*          int dia - Dia da data do voo
*          int mes - Mês da data do voo
*          int ano - Ano da data do voo
*          int hora - Hora de partida do voo
*          int minuto - Minuto de partida do voo
*          int codigoTripulacao - Código da tripulação responsável pelo voo
*
* PARAMETERS : 
* RETURN :
* Type : void
*
* Error: Não há tripulação cadastrada, 
*        Dia inválido: deve estar entre 1 e 31 e deve ser um número.
*        Mês inválido: deve estar entre 1 e 12 e deve ser um número.
*        Ano inválido: deve ser entre 2024 e 2030 e deve ser um número.
*        Hora inválida:  deve estar entre 0 e 23 e deve ser um número.
*        Minuto inválido: deve estar entre 0 e 59 e deve ser um número.
*        Código de tripulação inválido: Tripulação deve existir e não pode estar em uso.
*        Código de avião inválido: Codigo de avião não pode estar em uso e deve ser um número.
*        Tarifa invalida: Tarifa não pode ser negativa e deve ser um número.
*        Falta de piloto ou copiloto: status do voo será inativo.
*
*****************************************************************************/
void Voo::cadastroVoo()
{
    system("chcp 65001 > nul");
    system("cls");
    Voo voo;
    if (contagemVoo >= MAX_VOOS)
    {
        cout << "Limite de voos cadastrados atingido!" << endl;
        return;
    };

    string origem, destino;
    int codigoAviao, tarifa, status, dia, mes, ano, hora, minuto, codigoTripulacao;
    bool diaValido = false, mesValido = false, anoValido = false, horaValida = false, minutoValido = false, tripulacaoValida = false, codigoAviaoValido = false;
    bool temPiloto = false;
    bool temCopiloto = false;
    bool tripulacaoEmUso = false;
    
    

    if (tripulacaoVet.empty()) {
        cout << "Não há tripulação cadastrada. Cadastre uma tripulação antes de cadastrar um voo." << endl;
        cout << "Pressione 'ENTER' para voltar" << endl;
        cin.get();
        return; 
    }
    cout << "Informe a origem do voo." << endl;
    cout <<"Origem: ";
    getline(cin, origem);
    while (origem == "")
        {
            cout << "Erro: espaço em branco. Digite a origem do voo para prosseguir." << endl;
            getline(cin, origem);
        }
    voo.setOrigem(origem);

    do{   
        cout << "Informe o destino do voo." << endl;
        cout << "Destino: ";
        getline(cin, destino);
        while (destino == "")
        {
            cout << "Erro: espaço em branco. Digite o destino do voo para prosseguir." << endl;
            getline(cin, destino);
        }
        if(destino == origem){
            cout << "O destino deve ser diferente da origem." << endl;
        }
    }while(destino == origem);

    voo.setDestino(destino);

    cout << "Informe a data do voo." << endl;

    while (!diaValido)
    {
        
        cout << "Dia (1-31): ";
        while(!(cin >> dia)){
        cout << "Entrada inválida, insira um número." << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        voo.setDia(dia);
        diaValido = (dia > 0 && dia <= 31);
        
    }

    while (!mesValido)
    {
        cout << "Mes (1-12): ";
        while(!(cin >> mes)){
        cout << "Entrada inválida, insira um número." << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        voo.setMes(mes);
        mesValido = (mes > 0 && mes <= 12);
        
    }

    while (!anoValido)
    {
        
        cout << "Ano: (2024-2030): ";
        while(!(cin >> ano)){
        cout << "Entrada inválida, insira um número." << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        voo.setAno(ano);
        anoValido = (ano > 2023 && ano <= 2030);
    }


    while (!horaValida || !minutoValido)
{
    cout << "Digite o horário do voo (HH:MM): ";
    char doisPontos;
    

    if (cin >> hora >> doisPontos >> minuto) {
        if (doisPontos == ':' && hora >= 0 && hora <= 23 && minuto >= 0 && minuto <= 59) {
            voo.setHora(hora);
            voo.setMinuto(minuto);
            horaValida = true;
            minutoValido = true;
        } else {
            cout << "Horário inválido! Verifique o formato e os valores (HH:MM) com Horas entre 00 e 23 e Minutos entre 00 e 59." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    } else {
        cout << "Entrada inválida! Por favor, insira números no formato HH:MM." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

    while (!tripulacaoValida) {
    cout << "Informe o código da tripulação: ";
     while(!(cin >> codigoTripulacao)){
        cout << "Entrada inválida, insira um número." << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    cin.ignore();
    
    tripulacaoValida = false;
    
    for (int i = 0; i < tripulacaoVet.size(); i++) {
    if (tripulacaoVet[i].getCodigoTripulacao() == codigoTripulacao) {
        if (tripulacaoVet[i].getTripulacaoEmUso()) {
            cout << "Tripulação já está cadastrada em outro voo." << endl;
            cout << "Pressione 'ENTER' para voltar" << endl;
            cin.get();
            system("cls");
            return;
        }
        tripulacaoVet[i].setTripulacaoEmUso(true);
        tripulacaoValida = true;
    }
}
    
    if (!tripulacaoValida) {
        cout << "Código de tripulação inválido. Tente novamente." << endl;
        }
    }

    while(!codigoAviaoValido){
    cout << "Informe o código do avião: ";
     while(!(cin >> codigoAviao)){
        cout << "Entrada inválida, insira um número." << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        
    codigoAviaoValido = true; 
    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].getCodigoAviao() == codigoAviao) {
            cout << "Código de avião já está em uso." << endl;
            codigoAviaoValido = false; 
        }
    }

    if (codigoAviaoValido) {
        voo.setCodigoAviao(codigoAviao);
    }
}

    cout << "Informe a tarifa: ";
     while(!(cin >> tarifa) || tarifa < 0){
        cout << "Entrada inválida, tente novamente." << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    voo.setTarifa(tarifa);

    vector<Tripulacao>& tripulantes = tripulacaoVet[codigoTripulacao - 1].getTripulantes();  // Acessa a tripulação específica

    for (int j = 0; j < tripulantes.size(); j++) {
    
        if (tripulantes[j].getCargo() == "Piloto") {
            temPiloto = true;
        }
        
        if (tripulantes[j].getCargo() == "Copiloto") {
            temCopiloto = true;
        }
        
    }

    if (temPiloto && temCopiloto) {
        cout << "Voo ativo" << endl;
        status = 1;
        voo.setStatus(status);
    } else {
        cout << "Voo inativo, falta piloto ou copiloto" << endl;
        status = 2;
        voo.setStatus(status);
    }

    contagemVoo++;
    voo.setCodigoVoo(contagemVoo);

    voos.push_back(voo);

    voo.salvarVoos();
    cout << "Voo cadastrado com sucesso!"<<endl;
    cout << "Pressione 'ENTER' para voltar" << endl;

    cin.get();

}

/***********************************************************************
* NAME : void Voo::listarVoo()
* DESCRIPTION : Lista todos os voos cadastrados 
*               e exibe suas informações detalhadas.
* INPUTS :
* PARAMETERS : 
* RETURN :
* Type : void
* Error code :
* Values : Se houver voos cadastrados, exibe as informações detalhadas
*          de cada voo: código do voo, código do avião, origem, destino,
*          data, horário, tarifa e status.
*          Caso não possua voos cadastrados, 
*          exibe uma mensagem informando que não há voos cadastrados.
************************************************************************/
void Voo::listarVoo()
{
    system("cls");
    if (contagemVoo == 0)
    {
        cout << "Nenhum voo cadastrado" << endl;
    }
    else
    {
        for (int i = 0; i < contagemVoo; i++)
        {
            cout << endl;
            cout << "       Informações do Voo:" << voos[i].getCodigoVoo() << endl;
            cout << "+---------------------------------+"<<endl;
            cout << "| Tripulação do Voo: " << tripulacaoVet[i].getCodigoTripulacao() << endl;
            cout << "| Código de voo: " << voos[i].getCodigoVoo() << endl;
            cout << "| Código do avião: " << voos[i].getCodigoAviao() << endl;
            cout << "| Local de origem: " << voos[i].getOrigem() << endl;
            cout << "| Local de destino: " << voos[i].getDestino() << endl;
            cout << "| Data: " << setfill('0') << setw(2) << voos[i].getDia() << "/" << setfill('0') << setw(2) << voos[i].getMes() << "/" << voos[i].getAno() << endl;
            cout << "| Horário: " << setfill('0') << setw(2) << voos[i].getHora() << ":" << setfill('0') << setw(2) << voos[i].getMinuto() << endl;
            cout << "| Tarifa: " << voos[i].getTarifa() << endl;
            cout << "| Status: " <<voos[i].getStatus() << endl;
            cout << "+---------------------------------+"<<endl;
        }
    }

    cout << "Pressione 'ENTER' para voltar" << endl;
    cin.get();
}