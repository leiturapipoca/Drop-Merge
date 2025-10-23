# 🧮 Dpop Meros — Clone de 2048 Vertical em C

**Dpop Meros** é um jogo desenvolvido em **C**, inspirado no clássico *2048*, porém com uma dinâmica **vertical**, sistema de **pontuação multiplicativa** e um **ranking binário persistente**.  
O jogador posiciona blocos numéricos em colunas e, quando números iguais se tocam, eles se fundem multiplicando seus valores.  
A cada 10.000 pontos, o jogador ganha um **martelo** para quebrar blocos indesejados.

---

## 📚 Sumário

- [🎮 Funcionalidades Principais](#-funcionalidades-principais)
- [🧩 Estrutura do Projeto](#-estrutura-do-projeto)
- [🧠 Estrutura de Dados](#-estrutura-de-dados)
- [⚙️ Principais Funções](#️-principais-funções)
- [💥 Regras de Fusão](#-regras-de-fusão)
- [🧱 Sistema de Martelos](#-sistema-de-martelos)
- [🏆 Ranking](#-ranking)
- [🧹 Interface e Exibição](#-interface-e-exibição)
- [🧑‍💻 Tecnologias Usadas](#-tecnologias-usadas)
- [📸 Exemplo de Saída](#-exemplo-de-saída)
- [🧾 Licença](#-licença)

---

## 🎮 Funcionalidades Principais

✅ **Tabuleiro 10×5:** blocos “caem” até o fundo da matriz.  
✅ **Fusão automática:** números iguais se unem com multiplicadores.  
✅ **Gravidade realista:** blocos acima de espaços vazios descem automaticamente.  
✅ **Martelos:** a cada 10.000 pontos, o jogador ganha um martelo.  
✅ **Ranking persistente:** pontuações salvas no arquivo `ranking.bin`.  
✅ **Menus interativos:** opções de jogar, ver ranking, instruções e configurações.  
✅ **Armazenamento binário:** ranking gravado em formato eficiente.  

---

## 🧩 Estrutura do Projeto

| Arquivo | Descrição |
|----------|------------|
| `main.c` | Contém toda a lógica e execução do jogo |
| `ranking.bin` | Armazena o ranking de jogadores em formato binário |
| `numeros.txt` | Usado para leitura de números gerados ou salvos (placeholder) |

---
