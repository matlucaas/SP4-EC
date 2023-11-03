# Sprint 4 Edge Computing - "Timer Pomodoro com aplicação IoT"
Realizado pelos alunos:
- Bruno Bastos - RM: 550416
- Gabriel Freitas - RM: 550187
- Guilherme Daher - RM: 98611
- Matheus Lucas - RM: 99505
- Lucas Vassão - RM: 98607

## Sobre
Este projeto consiste em um temporizador para ajudar o usuário a se manter focado nas suas atividades do dia a dia. Mas como um temporizador pode ajudar no foco? Com base na técnica pomodoro isso é possível, dividindo o fluxo de trabalho em blocos de concentração intensa melhorando a agilidade do cérebro e estimulando o nosso foco.

## Componentes do protótipo
Para montar utilize a imagem do protótipo nos arquivos:
- Placa Arduino (utilizamos o Arduino Uno R3)
- Jumper Cables
- Led RGB
- Push Button
- 3 resistores de 220 ohms
- Buzzer / Piezo
- Cabo USB tipo A/B
- Placa WiFi/Bluetooth para o Arduino

## O que é necessário para utilizar a plataforma IoT
- Computador com acesso à internet
- Criar uma conta no site https://tago.io/
- Entrar no link: https://64ee9225f71df1000900a231.tago.run/
- Fazer login com o email(testetago@teste.com) e senha(12345678)
- Clicar no botão localizado na barra lateral esquerda "Sprint 4"

## Como os dados são enviados
Com sua conta na plataforma, adicione o seu dispositivo Arduino na plataforma e crie uma variável para receber seus valores, e vincule seu protótipo com a plataforma, e para continuar precisamos entender como o protótipo funciona: 
- Basicamente ao ser iniciado o led é ligado com a cor branca, indicando o tempo de foco;
- Depois de 30 segundos no tempo de foco, ele fica vermelho e o buzzer começa a apitar, indicando que o usuário precisa clicar no botão;
- Ao clicar no botão o usuário envia o dado de que ele está presente e ativou o modo de descanso, pois caso não clique só indica que ele está distraído fazendo algo em outro lugar, por exemplo;
- Clicando no botão, uma luz mais azul ativa, indicando que o usuário está no tempo de descanso, durando 10 segundos;
- São 4 ciclos de foco, e no último deles o led fica da cor vermelha e piscando, indicando que o usuário pode desligar o protótipo e ter um descanso maior, entre 20 e 30 minutos;
- É importante lembrar que caso o usuário não clique no botão alguma vez, o tempo de foco não vai ser validado, uma vez que só irá ser finalizado ao usuário ter clicado no botão 3 vezes, e o último descanso é livre;
- Com os dados enviados para a plataforma, o usuário pode ver os dados no dashboard com as informações citadas anteriormente. 

Uma imagem para entendermos melhor de o dado sai e até onde ele vai, ou seja, a arquitetura do IoT em si:
![Arquitetura](https://cdn.discordapp.com/attachments/866892150670884884/1153025685682667581/arquitetura.png)

## Link do simulador Arduino (Tinkercad)
- https://www.tinkercad.com/things/eEFsQHdn1XA

## Link vídeo explicativo
Nesse vídeo, tudo isso foi explicado de forma simples (Lembrando que esse é o vídeo da sprint anterior, a diferença agora é que criamos o dispositivo para trabalhar com MQTT e não mais com HTTP):
- https://youtu.be/IVgd-Dzep40?si=UPMEOP1ckMmuwHYX
