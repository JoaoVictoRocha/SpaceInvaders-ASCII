# 👾 Space Invaders ASCII

Projeto desenvolvido para a disciplina de Programação Orientada a Objetos (POO), que implementa uma versão do clássico **Space Invaders** utilizando apenas caracteres ASCII em terminal.

## 🎮 Sobre o jogo

O jogo é uma adaptação do clássico arcade onde o jogador controla uma nave que se movimenta horizontalmente na parte inferior da tela e deve destruir os inimigos antes que eles o destruam.

Toda a interface gráfica é renderizada diretamente no terminal utilizando caracteres ASCII.

## ⚙️ Funcionalidades

- Movimento lateral da nave
- Sistema de disparo
- Inimigos que se movimentam e disparam
- Detecção de colisão (tiros x inimigos)
- Sistema básico de pontuação
- Execução totalmente em terminal (sem interface gráfica)

## 🧱 Tecnologias utilizadas

- Linguagem: C++
- Execução em ambiente de terminal

## 🕹️ Controles

| Tecla | Ação |
|------|------|
| ← / → | Movimentar nave |
| Espaço | Atirar |
| ESC | Sair do jogo |

## ▶️ Como executar

### 1. Clonar o repositório
```bash
git clone https://github.com/JoaoVictoRocha/SpaceInvaders-ASCII.git
```

### 2. Acesse a pasta do projeto
```bash
cd SpaceInvaders-ASCII
```

### 3. Compile o código
```bash
g++ src/*.cpp -o game
```
### 4. Execute o jogo
```bash
./game
```
