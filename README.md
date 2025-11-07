WAR - Nível Aventureiro

Simulação interativa de batalhas entre territórios inspirada no jogo WAR, desenvolvida em C.
O programa permite cadastrar territórios, distribuir tropas, e realizar ataques automáticos baseados em rolagens de dados.

📋 Descrição do Projeto

O objetivo é simular o comportamento estratégico do jogo WAR, permitindo:

Cadastrar vários territórios (com nomes e cores de exércitos);

Atribuir tropas iniciais aleatórias a cada território;

Executar batalhas automáticas entre territórios inimigos;

Exibir o estado atualizado do mapa após cada ataque.

O projeto é ideal para praticar conceitos de Estruturas de Dados e Alocação Dinâmica em C.

⚙️ Funcionalidades

✅ Cadastro dinâmico de territórios (usando calloc)
✅ Atribuição automática de cores de exércitos
✅ Geração aleatória de tropas iniciais
✅ Simulação de ataques entre territórios inimigos
✅ Validação de jogadas (ex: não atacar a si mesmo ou mesma cor)
✅ Exibição do mapa atualizado após cada batalha
✅ Liberação correta da memória (free)

🧠 Conceitos Aplicados

struct em C (representação de territórios)

Alocação dinâmica de memória (calloc / free)

Manipulação de strings (strcpy_s, fgets)

Controle de fluxo com while e if

Números aleatórios com rand() e srand(time(NULL))

Funções auxiliares e protótipos

Boas práticas de limpeza de buffer (limparBuffer())


🧩 Estrutura do Código
Função	Descrição
cadastrarTerritorios()	Cria e preenche dinamicamente os territórios.
exibirTerritorios()	Mostra o mapa atual e as tropas de cada território.
atacar()	Simula uma batalha entre atacante e defensor.
liberarMemoria()	Libera o espaço de memória alocado para os territórios.
limparBuffer()	Evita problemas com o scanf e o fgets.
