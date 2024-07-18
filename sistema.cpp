#include <iostream> // Inclui a biblioteca de entrada e saída
#include <memory> // Inclui a biblioteca de ponteiros inteligentes
#include <vector> // Inclui a biblioteca de vetor
#include <string> // Inclui a biblioteca de string

using namespace std; // Usando o namespace std para simplificar o código

// Estrutura Usuario
struct Usuario {
    string nome; // Nome do usuário
    vector<weak_ptr<Usuario>> dependencias; // Vetor de dependências usando std::weak_ptr para evitar ciclos de referência
    unique_ptr<int> recurso_exclusivo; // Recurso exclusivo gerenciado por std::unique_ptr

    // Construtor da estrutura Usuario que inicializa o nome e o recurso exclusivo
    Usuario(const string& nome) : nome(nome), recurso_exclusivo(nullptr) {}
};

// Vetor global de usuários
vector<shared_ptr<Usuario>> usuarios;

// Protótipos das Funções
void adicionarUsuario(const string& nome);
void adicionarDependencia(const string& nomeUsuario, const string& nomeDependencia);
void listarDependencias(const string& nomeUsuario);
void atribuirRecursoExclusivo(const string& nomeUsuario, int valor);
shared_ptr<Usuario> encontrarUsuario(const string& nome);
void procurarUsuario(const string& nome);

// Função para adicionar um novo usuário ao sistema
void adicionarUsuario(const string& nome) {
    usuarios.push_back(make_shared<Usuario>(nome)); // Adiciona um novo usuário ao vetor de usuários
    cout << "Usuario '" << nome << "' adicionado." << endl; // Exibe mensagem de confirmação
}

// Função para encontrar um usuário pelo nome
shared_ptr<Usuario> encontrarUsuario(const string& nome) {
    for (const auto& usuario : usuarios) { // Itera sobre todos os usuários
        if (usuario->nome == nome) { // Verifica se o nome do usuário corresponde ao nome procurado
            return usuario; // Retorna o usuário encontrado
        }
    }
    return nullptr; // Retorna nullptr se o usuário não for encontrado
}

// Função para adicionar uma dependência a um usuário
void adicionarDependencia(const string& nomeUsuario, const string& nomeDependencia) {
    auto usuario = encontrarUsuario(nomeUsuario); // Encontra o usuário pelo nome
    auto dependencia = encontrarUsuario(nomeDependencia); // Encontra a dependência pelo nome
    if (usuario && dependencia) { // Verifica se ambos os ponteiros não são nulos
        usuario->dependencias.push_back(dependencia); // Adiciona a dependência ao vetor de dependências do usuário
        cout << "Usuario '" << nomeDependencia << "' adicionado como dependencia de '" << nomeUsuario << "'." << endl; // Exibe mensagem de confirmação
    } else {
        cout << "Erro ao adicionar dependencia. Verifique os nomes dos usuarios." << endl; // Mensagem de erro
    }
}

// Função para listar todas as dependências de um usuário específico
void listarDependencias(const string& nomeUsuario) {
    auto usuario = encontrarUsuario(nomeUsuario); // Encontra o usuário pelo nome
    if (usuario) { // Verifica se o ponteiro do usuário não é nulo
        cout << "Dependencias de '" << usuario->nome << "':\n"; // Exibe o nome do usuário
        for (const auto& dependencia : usuario->dependencias) { // Itera sobre todas as dependências
            if (auto dep = dependencia.lock()) { // Converte std::weak_ptr para std::shared_ptr
                cout << "- " << dep->nome << "\n"; // Exibe o nome da dependência
            }
        }
    } else {
        cout << "Usuario nao encontrado.\n"; // Mensagem de erro se o usuário não for encontrado
    }
}

// Função para atribuir um valor ao recurso exclusivo de um usuário
void atribuirRecursoExclusivo(const string& nomeUsuario, int valor) {
    auto usuario = encontrarUsuario(nomeUsuario); // Encontra o usuário pelo nome
    if (usuario) { // Verifica se o ponteiro do usuário não é nulo
        usuario->recurso_exclusivo = make_unique<int>(valor); // Atribui o valor ao recurso exclusivo do usuário
        cout << "Recurso exclusivo de '" << nomeUsuario << "' atribuido com valor: " << valor << "." << endl; // Exibe mensagem de confirmação
    } else {
        cout << "Usuario nao encontrado.\n"; // Mensagem de erro se o usuário não for encontrado
    }
}

// Função para procurar um usuário pelo nome e exibir o nome se encontrado
void procurarUsuario(const string& nome) {
    auto usuario = encontrarUsuario(nome); // Encontra o usuário pelo nome
    if (usuario) { // Verifica se o ponteiro do usuário não é nulo
        cout << "Usuario encontrado: '" << usuario->nome << "'\n"; // Exibe o nome do usuário encontrado
    } else {
        cout << "Usuario '" << nome << "' nao encontrado.\n"; // Mensagem de erro se o usuário não for encontrado
    }
}

// Programa Principal
int main() {
    int escolha;
    string nomeUsuario, nomeDependencia;
    int valor;

    do {
        cout << "\nMenu:\n";
        cout << "1. Adicionar Usuario\n";
        cout << "2. Adicionar Dependencia\n";
        cout << "3. Listar Dependencias\n";
        cout << "4. Atribuir Recurso Exclusivo\n";
        cout << "5. Procurar Usuario\n"; // Nova opção no menu
        cout << "6. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> escolha;

        switch (escolha) {
            case 1:
                cout << "Digite o nome do usuario: ";
                cin >> nomeUsuario;
                adicionarUsuario(nomeUsuario);
                break;
            case 2:
                cout << "Digite o nome do usuario: ";
                cin >> nomeUsuario;
                cout << "Digite o nome da dependencia: ";
                cin >> nomeDependencia;
                adicionarDependencia(nomeUsuario, nomeDependencia);
                break;
            case 3:
                cout << "Digite o nome do usuario: ";
                cin >> nomeUsuario;
                listarDependencias(nomeUsuario);
                break;
            case 4:
                cout << "Digite o nome do usuario: ";
                cin >> nomeUsuario;
                cout << "Digite o valor do recurso exclusivo: ";
                cin >> valor;
                atribuirRecursoExclusivo(nomeUsuario, valor);
                break;
            case 5:
                cout << "Digite o nome do usuario: ";
                cin >> nomeUsuario;
                procurarUsuario(nomeUsuario);
                break;
            case 6:
                cout << "Saindo...\n";
                break;
            default:
                cout << "Opcao invalida! Tente novamente.\n";
                break;
        }
    } while (escolha != 6);

    return 0; // Finaliza o programa
}
