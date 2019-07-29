// NotacaoPosFixa.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
/*
Programa para ler expressao infixa, e exuibir sua posfixa
* RAILANDER JOSE DOS SANTOS
* FAULDADE UNICA DE IPATINGA - 08/2018
*/
#include <iostream>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <stack>

using namespace std;

int prioridade(char op) {//metodo que retorna a prioridade de um dado operador
	switch (op) {
	case '^':
		return 3;
		break;
	case '*':
	case '/':
		return 2;
		break;
	case '+':
	case '-':
		return 1;
		break;
	default:
		return -1;
	}
}

/*bool ehOperador(char op){
   if(op== '^' || op== '/' || op== '*' || op== '+' || op== '-' )
	   return true;
   else
	   return false;
}*/

bool ehExp(char exp) {//método que verifica se entrada é ou nao uma expressao valida
	if ((exp >= 'a' && exp <= 'z') || (exp >= 'A' && exp <= 'Z') ||
		(exp >= '0' && exp <= '9'))
		return true;
	else
		return false;
}

void conversor(string entrada) {//método principal, que recebe uma expressão informada e a converte
	string posFixa; //string para armazenar expressao posfixa
	stack<char>pilhaOperadores; //pilha para armazenar operadores
	pilhaOperadores.push('#');
	int t = entrada.length();
	for (int i = 0; i < t; i++) {//percorre todos os caracteres da expressão informada
		if (ehExp(entrada[i]) == true) {//verifica pela funçao se alfabeto é valido
			posFixa += entrada[i];//se for armazena a primeira letra a expressao posfixa
		}
		else//caso nao for pertencente ao alfabeto
			if (entrada[i] == '(') {//caso for abetura de parentese
				pilhaOperadores.push(entrada[i]);//insira na pilha de operadores o caractere de entrada indice i
			}
			else//caso nao for abertura de parentese
				if (entrada[i] == ')') { //se entrada for fechamento de parentese 
					while (pilhaOperadores.top() != '#' && pilhaOperadores.top() != '(') {//enquanto topo da pilha for diferente da introdução inicial e topo de pilha difetente de abertura de parentese
						char c = pilhaOperadores.top();//converte conteudo do topo da pilha em char e o armazene na variavel
						pilhaOperadores.pop();//retire o que esta no topo
						posFixa += c;//concatene ao conteudo da string pos fixa esta variavel
					}
					if (pilhaOperadores.top() == '(') {//se topo de pilha operadores for abertura de parenteses
						char c = pilhaOperadores.top();
						pilhaOperadores.pop(); //retire o do topo
					}
				}
				else {//caso nehuma das anterioes (se for operador)
					while (pilhaOperadores.top() != '#' && prioridade(entrada[i]) <= prioridade(pilhaOperadores.top())) {//enquanto topo da pilha de operadores for diferente de char inicial, e prioridade de entrada for <= prioridade da pilha
						char c = pilhaOperadores.top();//armazene o conteudo do topo da pilha em uma variavel
						pilhaOperadores.pop();//retire do topo da pilha
						posFixa += c;//adcione-a na string de posfixa
					}

					pilhaOperadores.push(entrada[i]);//adcione caracter do indice i a pilha de operadores
				}
	}

	while (pilhaOperadores.top() != '#') {//enqunto houver algo alem do caracter inicial na pilha de operadores
		char c = pilhaOperadores.top();//faça char receber o topo da pilha de operadores
		pilhaOperadores.pop();//retire caracter do topo
		posFixa += c;//adcione o a string posfixa
	}
	cout << "\n\n" << posFixa;//imprime
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	string entrada;
	cout << "\nInforme uma expressão infixa:";
	cin >> entrada;
	conversor(entrada);

	return 0;
}

