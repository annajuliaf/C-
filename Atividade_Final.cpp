/*  Anna Júlia Ferreira de Souza, Luana Camilly dos Santos e Samuel Gomes Costa
    20/07/2021 ~ 29/07/2021
    O seguinte programa faz a entrada de alguns atributos de uma quantidade MAX de pessoas, 
    atributos como CPF, nome, altura e outros. Posteriormente, ele apresenta um menu de opcoes em
    que o usuario pode escolher até que deseje sair do programa.
*/

#include <iostream>
#include <limits>
using namespace std;

const int MAX = 2;

//Entrada da data de nascimento de uma pessoa
struct Data{
    int dia;
    int mes;
    int ano;
};

//Estrutura que armazena os dados das pessoas
struct Pessoa{
    int CPF[11];
    string nome;
    Data dtNasc;
    int idade;
    float altura, peso, IMC;
};

//Pedido do CPF de cada pessoa
void entradaCPF(int cpf[]){
    cout << "ENTRADA de CPF" << endl;
    for(int i=0; i<11; i++){
        cout << "Entre com o " << i+1 << "° digito: ";
        cin >> cpf[i];

        while(cpf[i]>=10 || cpf[i]<0){
            cout << "Dígito inválido!" << endl;
            cout << "Entre com o " << i+1 << "º digito: ";
            cin >> cpf[i];
        }
    }
}

//Verificação do CPF de acordo com seus dígitos verificadores
bool validaCPF(int cpf[]){
    int d1, d2, count=0;
    //Verificação do primeiro dígito
    for(char i = 0; i < 9; i++)
        count += (cpf[i] * (10 - i));
    count %= 11;

    if(count < 2)
        d1 = 0;
    else
        d1 = 11 - count;
    
    
    //Verificação do segundo dígito
    count = 0;
    for(char i = 0; i < 10; i++)
        count += (cpf[i] * (11 - i));
    count %= 11;

    if(count < 2)
        d2 = 0;
    else
        d2 = 11 - count;
    
        
        
    if(d1 == cpf[9] && (d2 == cpf[10]))
        return true;
    else
        return false;
}

//Faz a entrada de um CPF válido de acordo com seus dígitos verificadores
void entradaCPFValido(int cpf[]){
    entradaCPF(cpf);
    while(!validaCPF(cpf)){
        entradaCPF(cpf);
    }
}

//Imprime o CPF no formato XXX.XXX.XXX-XX
void imprimeCPF(int cpf[]){
    for(int i=0; i<9; i++){
        cout << cpf[i];
        if(i==2 || i==5)
            cout << ".";
    }
    cout << "-";
    cout << cpf[9] << cpf[10];
}

//Entrada de um nome
void entradaNome(string &nome){
    cout << "Entre com o nome: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nome);
}

//Entrada do dia, mês e ano em dt
void entradaData(Data &dt){
    cout << "Entre com o dia: ";
    cin >> dt.dia;
    cout << "Entre com o mes: ";
    cin >> dt.mes;
    cout << "Entre com o ano: ";
    cin >> dt.ano;
}

//Verifica se um ano é bissexto
bool anoBissexto(int ano){
    return (ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0;
}

//Verifica se uma data é válida
bool validaData(Data dt){
    if(anoBissexto(dt.ano) == false && dt.dia > 28 && dt.mes == 2)
        return false;
    else if(dt.mes == 2 && dt.dia >= 30)
        return false;
    else if (dt.dia >= 31 && (dt.mes == 4 ||  dt.mes == 6 ||  dt.mes == 9 || dt.mes == 11))
        return false;
    else
         return (dt.dia >= 1 && dt.dia <= 31 && dt.mes <= 12 && dt.mes >= 1 && dt.ano >= 1);
}

//Entrada da data de nascimento
void entradaDataNascimentoValido(Data &dt){
    entradaData(dt);
    while(!validaData(dt)){
        cout << "Data invalida!" << endl;
        entradaData(dt);
    }
}

//Com a data de nascimento, retorna a idade de uma pessoa
int calculaIdade(Data dtNasc){
    int dias1, dias2, idade_dias;
    float idade;
    dias1 = dtNasc.ano*365 + dtNasc.mes*30 + dtNasc.dia;
    dias2 = 2021*365 + 7*30 + 13;
    idade_dias = dias2 - dias1;
    
    idade = idade_dias / 365;
    return idade;
}

//Entrada da altura
void entradaAltura(float &alt){
    cout << "Entre com a altura: ";
    cin >> alt;

    while(alt<=0 || alt >=3){
        cout << "Altura inválida!" << endl;
        cout << "Entre com a altura: ";
        cin >> alt;
    }
}

//Faz a entrada do peso, validando-o. Sai da função com um peso válido (positivo e menor que 500.0)
void entradaPeso(float &peso){
    cout << "Entre com o peso: ";
    cin >> peso;

    while(peso<=0 || peso >=500.0){
        cout << "Peso inválido!" << endl;
        cout << "Entre com o peso: ";
        cin >> peso;
    }
}

//Retorna o IMC de uma pessoa
float calculaIMC(float p, float a){
    return p/(a*a);
}

//Faz a entrada das MAX pessoas de uma vez
void entrada(Pessoa p[]){
    for(int i=0; i<MAX; i++){
        cout << "==========================================" << endl;
        cout << "Pessoa #" << i+1 << endl;
        entradaCPFValido(p[i].CPF);
        entradaNome(p[i].nome);
        entradaDataNascimentoValido(p[i].dtNasc);
        p[i].idade = calculaIdade(p[i].dtNasc);
        entradaAltura(p[i].altura);
        entradaPeso(p[i].peso);
        p[i].IMC = calculaIMC(p[i].peso, p[i].altura);
        cout << endl << "Pessoa cadastrada com sucesso!" << endl;
    }
}

//Imprime os dados (atributos) de uma pessoa
void imprimePessoa(Pessoa p){
    cout << "CPF: ";
    imprimeCPF(p.CPF);
    cout << endl;
    cout << "Nome: " << p.nome << endl;
    cout << "Idade: " << p.idade << endl;
    cout << "Peso: " << p.peso << endl;
    cout << "Altura: " << p.altura << endl;
    cout << "IMC: " << p.IMC << endl;
}

//Imprime os dados/atributos de todas as MAX pessoas
void imprimeTodasPessoas(Pessoa p[]){
    for(int i=0; i<MAX; i++){
        cout << "PESSOA #" << i+1 << endl;
        imprimePessoa(p[i]);
        cout << endl;
    }
}

//Retorna true se os dois CPFs são iguais, e false caso contrário
bool verificaCPFsIguais(int cpf1[], int cpf2[]){
    for (int i=0; i < 11; i++)
        if (cpf1[i] != cpf2[i])
            return false;
    return true;
}

//Imprime os dados de uma pessoa, dado seu CPF como parâmetro
void imprimePessoaCPF(Pessoa p[], int cpf[]){
    for(int i=0; i<MAX; i++){
        if(verificaCPFsIguais(p[i].CPF, cpf))
            imprimePessoa(p[i]);
    } 
    if(verificaCPFsIguais(p->CPF, cpf) == false)
        cout << "Não existe pessoa cadastrada com esse CPF" << endl;
}

//Imprime os dados das pessoas que estão no sobrepeso ou maior (IMC > 25.0)
void imprimePessoasSobrepesoOuMaior(Pessoa p[]){
    int maiorPeso = p[0].IMC;
    for(int i=0; i<MAX; i++){
        if(p[i].IMC > maiorPeso){
            maiorPeso = p[i].IMC;
            if(maiorPeso > 25.0){
                cout << "A(s) seguinte(s) pessoa(s) está(ão) com sobrepeso: " << endl;
                imprimePessoa(p[i]);
                cout << endl;
            }
        }
    }
    if(maiorPeso <= 25)
        cout << "Não existe ninguém com sobrepeso" << endl;
}

//Retorna o nome da pessoa mais alta
void nome_pessoaMaisAlta(Pessoa p[]){
    int maiorAltura = p[0].altura;
    string NomeMaiorAltura = p[0].nome;

    for(int i=0; i<MAX; i++){
        maiorAltura = p[i].altura;
    }

    if(maiorAltura > p[0].altura)
        cout << "A segunda pessoa é mais alta que a primeira";
    if(maiorAltura < p[0].altura)
        cout << "A primeira pessoa é mais alta que a segunda";
    if(maiorAltura == p[0].altura)
        cout << "Ambas as pessoas são do mesmo tamanho";
}

//Mostra a relação entre as idades das pessoas cadastradas
void relacaoIdade(Pessoa p[]){
    int maiorIdade = p[0].idade;
    for(int i=0; i<MAX; i++){
        maiorIdade = p[i].idade; 
    }
    cout << "Considerando a data atual (13/07/2021): ";
    if(maiorIdade > p[0].idade)
        cout << "A segunda pessoa é mais velha que a primeira";
    if(maiorIdade < p[0].idade)
        cout << "A segunda pessoa é mais nova que a primeira";
    if(p[0].idade == maiorIdade)
        cout << "Ambas tem a mesma idade";
}

//Imprime os dados de uma pessoa, dado seu nome como parâmetro
void imprimePessoaNome(Pessoa p[], string nome){
    entradaNome(nome);
    for(int i=0; i<MAX; i++){
         if(p[i].nome == nome){
            cout << "Aqui estão os dados dessa pessoa: " << endl;
            imprimePessoa(p[i]);
         }
    }
}

// Imprime o menu de opções e retorna a opção que o usuário digitou
int imprimeMenu(){
    int op;
    cout << "==========================================" << endl;
    cout << "MENU\n"
         << "0 - Sair\n"
         << "1 - Todas as pessoas\n"
         << "2 - Pessoa por CPF\n"
         << "3 - Pessoas a partir do sobrepeso\n"
         << "4 - Pessoa mais alta\n"
         << "5 - Relação das idades\n"
         << "6 - Pessoa por nome\n"
         << "Entre com a opção: ";
    cin >> op;
    cout << endl;
    return op;
}

int main(){
    setlocale(LC_ALL, "Portuguese"); // para aceitar acentuação e cedilha nas frases
    int op, cpf[11];
    Pessoa p[MAX];

    // Faz a entrada de todas as pessoas (vetor p) com os seus atributos
    entrada(p);

    do{
        op = imprimeMenu();
        switch(op){
            case 0:
                cout << "Saindo....";
                cout << endl;
                break;
            case 1:
                imprimeTodasPessoas(p);
                cout << endl;
                break;
            case 2:
                entradaCPF(cpf);
                cout << endl;
                imprimePessoaCPF(p, cpf);
                cout << endl;
                break;
            case 3:
                imprimePessoasSobrepesoOuMaior(p);
                cout << endl;
                break;
            case 4:
                nome_pessoaMaisAlta(p);
                cout << endl;
                break;
            case 5:
                relacaoIdade(p);
                cout << endl;
                break;
            case 6:
                imprimePessoaNome(p, p->nome);
                break;
            default:
                cout << "Opcao invalida!";
        }
    }while(op != 0);

    return 0;
}