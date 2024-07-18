#include <iostream> //biblioteca de entrada e saída
#include <memory> //biblioteca e ponteiros inteligentes 
#include  <vector> //biblioteca do vetor
#include <string> //biblioteca de string

using namespace std; 

//estrutura do usuario
struct Usuario
{
    string nome;//nome do usuarios
    vector<weak_ptr<Usuario >> dependencias;//vetor de dependêncai usando std::weak_ptr para evitar ciclos de referência
    unique_ptr<int> recurso_exclusivo;//recusrso exclusivo gerenciado por std::unique_ptr

    // Construtor da estrutura Usuario que inicializa o nome e o recurso exclusivo
    Usuario(const string& nome) : nome(nome), recurso_exclusivo(nullptr){}
};

vector<shared_ptr<Usuario>> usuarios;//vetor global de usurarios


//PROTOTIPAÇÃO DAS FUNÇÕES

void adicionarUsuario(const string& nome);
void adicionarDependencia (const string& nomeUsuario, const string& nomeDependencia);
void listarDependencias(const string&nomeUsuario);
void atribuirRecursosExclusivo(const string& nomeUsuario, int valor);
shared_ptr<Usuario> encontrarUsurario(const string& nome);

//função para adicionar um novo usuário no sistema
void adicionarUsuario(const string& nome){
    usuarios.push_back(make_shared <Usuario> (nome));// adiciona um novo usuário ao vetor de usuários
    cout << "Usuario '" << nome << "' adicionado." << endl; // Exibe mensagem de confirmação

}


//função para encontrar um usuário pelo nome 

shared_ptr<Usuario> encontrarUsurario(const string& nome){
    for (const auto& usuario : usuarios ){ //itera sobre todos os usuarios
        if (usuario -> nome == nome){//verifica se o nome do usuário corresponde ao nome encontrado
            return usuario;//retorna o usuario encontrado
        }
    }
    return nullptr;//retorna nultpr se o usuario não for encontrado
}

//função para adicionar uma dependência a um usuário
void adicionarDependencia (const string& nomeUsuario, const string& nomeDependencia){
    auto usuario = encontrarUsurario(nomeUsuario);// encontra o usuário pelo nome
    auto dependencia = encontrarUsurario(nomeDependencia); //encontra a dependencia pelo nome
    if (usuario && dependencia){ // veirica se ambos os ponteiro não são nulos
        usuario -> dependencias.push_back(dependencia);//adiciona a dependencia ao vetor de dependencia do usuário
        cout << "Usuario '" << nomeDependencia << "' adicionado como dependencia de '" << nomeUsuario << "'." << endl; // Exibe mensagem de confirmação

    }
}   


//função para listar todas as dependencias de um usuário específico

void listarDependencias(const string& nomeUsuario){
    auto usuario = encontrarUsurario(nomeUsuario);//encontra o usuário pelo nome
    if (usuario){//veriifica se o ponterio do usuario não é mulo
        cout << "Dependencias de "  << usuario-> nome <<" :\n"; //exibi o nome do usuarios
        for (const auto& dependencia : usuario -> dependencias){ //itera sobre todas as dependências
            if (auto dep = dependencia.lock()){ //converte std::weal_ptr para std:: shared_ptr
                cout << "- "<< dep-> nome << "\n";  
            }
        }

    }else{
        cout << "usuaraio não encontrado.\n"; 
    }
}

//função para atribuir um valor ao recirso exlusivo de um usuário

void atribuirRecursoExclusivo(const string& nomeUsuario, int valor){
    auto usuario = encontrarUsurario(nomeUsuario);//encontrar o usuario pelo nome
    if(usuario){//verifica se o ponteiro usuario não é nulo
        usuario -> recurso_exclusivo = make_unique<int>(valor);//atribui o valor ao rescuro exclusivo do usuário
        cout << "Recurso exclusivo de " << nomeUsuario << "' atribuido com valor: " << valor << "." << endl; // Exibe mensagem de confirmação

    }else{
        cout << "Usuario nao encontrado.\n"; // Mensagem de erro se o usuário não for encontrado

    }
}

// Programa Principal
int main() {
    adicionarUsuario("Alice"); // Adiciona o usuário "Alice"
    adicionarUsuario("Bob"); // Adiciona o usuário "Bob"
    adicionarUsuario("Carol"); // Adiciona o usuário "Carol"
    
    adicionarDependencia("Alice", "Bob"); // Adiciona "Bob" como dependência de "Alice"
    adicionarDependencia("Alice", "Carol"); // Adiciona "Carol" como dependência de "Alice"
    
    atribuirRecursoExclusivo("Alice", 42); // Atribui o valor 42 ao recurso exclusivo de "Alice"
    
    listarDependencias("Alice"); // Lista as dependências de "Alice"
    listarDependencias("Bob"); // Lista as dependências de "Bob"
    
    return 0; // Finaliza o programa
}