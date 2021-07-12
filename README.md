# Fox & Geese AI Problem

This project is an implementation of the [Fox-Geese game](https://www.mastersofgames.com/rules/fox-geese-rules.htm).

Esse projeto é uma implementação do jogo da [Raposa e Gansos](https://www.mastersofgames.com/rules/fox-geese-rules.htm).

# Uso
Para preparar o seu jogador para se comunicar com o controlador do
tabuleiro você deve alterar o seu programa para utilizar as funções
que enviam e recebem dados do controlador. O exemplo1 pode ajudar
nesta alteração.

Para testar o seu jogador você deve iniciar o servidor redis e
executar o controlador.

Para iniciar o servidor redis nos sistemas do DInf execute em um
terminal:

```
   $ redis-server redis.conf
```

Para iniciar o controlador execute em outro terminal:
```
   $ ./controlador r 50 0
```
Este comando inicia o controlador indicando que o jogador que começa é
o 'r' (raposa), a partida terá 50 movimentos e não há limite de tempo
para as jogadas. Para mais detalhes sobre os parâmetros do controlador
execute:
```
   $ ./controlador
```
Para conectar duas instâncias do exemplo2 ao controlador, uma de cada
lado do tabuleiro, execute em outros dois terminais os comandos:
```
   $ ./exemplo2 r
```
```
   $ ./exemplo2 g
```
Você pode testar o seu jogador jogando interativamente contra ele
usando o exemplo2. Basta executar o seu jogador em um terminal e o
exemplo2 em outro.
