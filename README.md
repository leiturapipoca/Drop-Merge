🎮 Dpop Meros - Um Híbrido de Tetris e 2048 em C
Bem-vindo ao Dpop Meros! Este é um projeto de jogo de puzzle desenvolvido em C puro, que combina a mecânica de queda de blocos do Tetris com a lógica de fusão de números do 2048. O projeto foi criado como um exercício acadêmico para aprofundar conhecimentos em algoritmos, manipulação de arquivos e os fundamentos do desenvolvimento de jogos no terminal.

🎯 O Objetivo
O objetivo é simples: impedir que a grade de 10x5 seja completamente preenchida! Para isso, você deve posicionar os números que caem de forma estratégica, combinando-os com números idênticos adjacentes. Cada fusão gera um novo número e mais pontos, limpando espaço no tabuleiro e permitindo que o jogo continue.

✨ Funcionalidades Principais
Mecânica de Fusão Dinâmica 🧠: Ao posicionar um bloco, ele verifica seus vizinhos (embaixo, à esquerda e à direita). Se houver blocos com o mesmo número, eles se fundem!

Sistema de Pontuação Exponencial 📈: A pontuação é calculada com base na quantidade de blocos fundidos de uma só vez. O novo bloco terá seu valor multiplicado por 2 elevado ao número de vizinhos combinados (novo_valor = valor_original * 2^vizinhos), incentivando combos maiores!

Combos em Cascata 💥: Uma única jogada pode criar uma reação em cadeia! Após uma fusão, o novo bloco pode se fundir novamente com seus novos vizinhos, levando a reviravoltas emocionantes.

Ferramenta Martelo 🔨: A cada 10.000 pontos, você ganha um "martelo". Essa ferramenta poderosa permite remover qualquer bloco do tabuleiro, sendo uma salvação estratégica em momentos críticos. O jogo só termina se o tabuleiro encher E você não tiver mais martelos!

Ranking Persistente 🏆: Seu nome e pontuação são salvos em um arquivo binário (ranking.bin) ao final de cada partida. O ranking é exibido em ordem decrescente, permitindo que você dispute as melhores pontuações.

Interface de Terminal Clássica 👾: Toda a experiência do jogo acontece diretamente no terminal, com uma grade visual que é atualizada a cada jogada.

Multiplataforma: O código foi escrito para ser compatível com Windows e sistemas baseados em Unix (Linux, macOS), graças à limpeza de tela condicional.

🛠️ Propósito e Aprendizado
Este projeto foi fundamental para aplicar e solidificar diversos conceitos da programação em C:

Manipulação de Arquivos: Leitura de um arquivo de texto (numeros.txt) para gerar a sequência de peças do jogo e leitura/escrita em um arquivo binário (ranking.bin) para persistir os dados do ranking.

Estruturas de Dados: Uso de structs para organizar os dados dos jogadores (nickname e pontuação) de forma limpa e eficiente.

Arrays Multidimensionais: Implementação da lógica do jogo sobre uma matriz 2D que representa o tabuleiro.

Algoritmos: Aplicação do algoritmo Bubble Sort para ordenar o ranking de jogadores.

Modularização: O código é organizado em funções com responsabilidades claras (menu, renderização da grade, lógica de verificação, etc.), tornando-o mais legível e fácil de manter.

Lógica de Jogo Complexa: Desenvolvimento de um loop de jogo robusto, com checagem de condições de vitória, derrota e interações em cascata.
