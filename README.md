# Campainha Inteligente

## Descrição

**Campainha Inteligente** é um projeto de IoT que proporciona uma maneira moderna e eficiente de notificar o proprietário de uma casa sobre a presença de visitantes na porta. Utilizando reconhecimento de voz offline, o sistema responde ao comando “**Open the door**”, enviando automaticamente uma requisição HTTP para uma API gratuita que notifica o proprietário em seu smartphone sobre a presença dos visitantes.

Desta maneira, seus visitantes serão tratados de forma atrativa e inovadora, tornando a experiência de chegada à residência única e envolvente.

Trata-se de uma versão 2.0 do projeto Campainha-Domiciliar, presente em meu github. A principal inovação é a detecção de voz offline, e não apenas o quão alto é o ruído ambiente.

## Funcionalidades

- Reconhecimento de voz offline utilizando o sensor **SEN0539-EN**.
- Controle por comando de voz para abrir a porta.
- Notificação automática para o smartphone do proprietário via API.
- Integração com o microcontrolador **ESP8266**.

## Tecnologias Utilizadas

- **Microcontrolador ESP8266**: Responsável pelo envio de requisições HTTP.
- **Sensor SEN0539-EN**: Utilizado para reconhecimento de voz offline
- **API HTTP**: API gratuita utilizada para o envio de notificações para o smartphone.
- **Linguagem C/C++**: Usada no desenvolvimento do firmware para o ESP8266.

## Instalação e Uso

### Pré-requisitos

- **ESP8266 x 1** configurado com o ambiente de desenvolvimento Arduino IDE ou PlatformIO.
- **Sensor SEN0539 Gravity: Voice Recognition Module x I2C & UART x 1** devidamente conectado ao ESP8266.B
- **Buzzer ativo**
- Conexão Wi-Fi para o envio das notificações via HTTP.
- Conta configurada para a API de notificações.

### Passos para Instalação

1. Clone este repositório:
   ```bash
   git clone https://github.com/seu-usuario/campainha-inteligente.git
2. Abra o projeto na Arduino IDE ou PlatformIO.
3. Instale as bibliotecas necessárias:
   - ESP8266WiFi
   - ESP8266HTTPClient
   - WiFiClientSecure
   - [DFRobot_DF2301Q](https://github.com/DFRobot/DFRobot_DF2301Q) (Bibliotecas de suporte ao SEN0539-EN).
4. Configure seu código com as credenciais de Wi-Fi e a URL da API de notificação, esta contendo os tokens do seu bot, uma chave de api, dentre outras
5. Compile e faça o upload do código para o ESP8266.

### Comando de Voz
O sistema irá identificar o comando de voz: "Open the door". Ao ser reconhecido, a API será acionada, enviando a notificação ao proprietário. Ao mesmo tempo, o módulo de voz emitirá um som de confirmação do comando, bem como um buzzer ativo irá tocar o som de uma campainha.

Caso o comando seja inválido, será tocado um sinal de acesso negado por parte do buzzer ativo.

### Estrutura do projeto
   ```bash
   ├── /Campainha-Inteligente-Telegram    # Versão do projeto com API Telegram gratuita
   ├── /Campainha-Inteligente-Whatsapp    # Versão do projeto com API Whatsapp gratuita
   ├── LICENSE                            # Arquivo de licença (CC0-1.0)
   └── README.md                          # Documentação do projeto
   ```

### Contribuições
Sinta-se à vontade para contribuir com melhorias e novas funcionalidades. Basta abrir uma pull request ou issue no repositório.

### Licença
Este projeto está disponível sob a licença CC0-1.0 (Domínio Público). Para mais detalhes, consulte o arquivo LICENSE.
