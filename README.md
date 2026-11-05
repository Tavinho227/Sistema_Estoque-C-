# Projeto Final - Sistema de Estoque (Tarefa 5)

Projeto em C para Dev-C++ 5.11, organizado em varios arquivos. Contempla os requisitos acumulados das Tarefas 1 a 5.

## Como abrir no Dev-C++

1. Extraia todos os arquivos desta pasta para uma pasta normal do Windows. **Nao abra de dentro do ZIP**.
2. Abra **Sistema_Estoque.dev** (nao o executavel .exe).
3. Se necessario, selecione **Executar > Reconstruir Tudo** (ou F11 / Compilar e Executar).
4. Os arquivos `.c` estao todos marcados com `Compile=1` e `Link=1` no projeto, para evitar erros de `undefined reference`.

Alternativa GCC: `gcc -std=c99 -Wall -Wextra main.c produto.c categoria.c util.c -o Sistema_Estoque`

## Menu

1. Cadastrar Produto
2. Listar Produtos
3. Pesquisar Produto (por codigo ou nome)
4. Alterar Estoque de um Produto (entrada/saida)
5. Remover Produto (exclusao logica)
6. Categorias (cadastrar/listar)
7. Sair

## Dados salvos

- `categorias.txt`: `codigo|nome`
- `produtos.txt`: `codigo|nome|prateleira|preco|quantidade|disponivel|categoria_codigo|ativo`
- Ao iniciar, carrega os dados existentes; ao alterar/cadastrar, salva os dados; ao sair, grava as duas listas.
- Os arquivos sao criados automaticamente na **pasta de trabalho da execucao**. O programa nao depende de arquivos existentes para iniciar.
- Produtos removidos continuam no arquivo com `ativo=0`, mas ficam invisiveis nas consultas e nao permitem que o mesmo codigo seja reutilizado.
- A disponibilidade (`disponivel`) e sempre atualizada automaticamente com base na quantidade.
- O nome do produto na pesquisa e comparado exatamente (`strcmp`), como pedido pelo professor.
- Um produto nao pode existir sem uma categoria cadastrada.

## Grupo

Richard Otavio dos Santos Salgado (50407198), Walisson de Melo Teixeira (49750780), Vinicius Prisca de Paula (49209931), Gustavo Araujo Lima Franco (49052632), Otavio Araujo Goncalves Ribeiro (49805240), Pedro de Souza Belvederesi (49603159) e Luigi Damasceno Silva (49052152).
