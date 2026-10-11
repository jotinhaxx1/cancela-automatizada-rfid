# 🚪 Protótipo de Sistema de Cancela Automatizada com Tecnologia RFID

Projeto e desenvolvimento de um **Protótipo de Controle de Acesso Veicular Automatizado** baseado em **Identificação por Radiofrequência (RFID)** e microcontrolador Arduino Uno, publicado na revista *Vértices* (Essentia Editora IFFluminense).

O sistema foi desenvolvido como uma solução de baixo custo, alta confiabilidade e operação sem contato físico para controle de fluxo de veículos em instituições de ensino (ex.: Instituto Federal Fluminense - IFF Campus Macaé), empresas e condomínios.

---

## 🛠️ Arquitetura de Hardware e Tecnologias

* **Microcontrolador:** Arduino Uno (Atmega328P) — Núcleo de processamento e controle
* **Leitor RFID:** Módulo RC522 (Frequência 13.56 MHz, comunicação via protocolo SPI)
* **Atuador Mecânico:** Servo Motor SG90 (Abertura/Fechamento incremental de 0° a 90°)
* **Interface de Sobrevida/Manual:** Push Button para acionamento secundário de emergência
* **Alimentação e Prototipagem:** Protoboard, cabos Jumpers e fonte de alimentação dedicada

---

## ⚡ Funcionamento do Sistema e Lógica de Controle

1. **Leitura e Validação RFID (Protocolo SPI):**
   * O módulo RC522 faz a leitura da tag/cartão aproximado.
   * O Arduino converte os bytes de UID para um valor numérico e compara com a matriz de cartões permitidos (`cartoesAutorizados[]`).
2. **Movimentação Incremental do Servo Motor:**
   * Para evitar pancadas e desgaste mecânico na barreira, a abertura (`abrirCancela()`) ocorre de forma suave em passos de **15 ms** até atingir 90°.
   * A cancela permanece aberta por **5 segundos** antes de iniciar o fechamento automático.
3. **Acionamento Manual Secundário:**
   * Um botão acoplado ao pino digital permite a liberação manual da cancela caso ocorra alguma falha na leitura da tag.

---

## 📊 Pesquisa de Mercado e Relevância

O projeto foi embasado em uma pesquisa de campo realizada com 56 participantes:
* **56,4%** consideram os métodos manuais de identificação lentos e obsoletos.
* **93%** apoiam a implementação de controle de acesso veicular automatizado.
* **72,7%** apontam a confiabilidade como o atributo principal de escolha do sistema.

---

## 👥 Autores e Instituição

* **Integrantes:** Bernardo Melo, Carolina Tavares, Henrique Graessler, João Pedro, João Victor, Roberto Zulo, Yuri Faria
* **Publicação/Afiliação:** Vértices (Essentia Editora IFFluminense) — Instituto Federal Fluminense (IFF)
