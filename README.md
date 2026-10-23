Aqui tens o ficheiro **`README.md`** completo e atualizado para o teu repositório no GitHub, estruturado com badges profissionais, sem emojis e com os devidos créditos ao autor **Manuel Sadi Kufika**:

```markdown
# BANKAI - Security Framework

<p align="center">
  <b>Uma ferramenta modular de auditoria de rede e segurança de alta performance desenvolvida em C.</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-00599C?style=flat&logo=c&logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/Author-Manuel%20Sadi%20Kufika-blueviolet?style=flat&logo=github&logoColor=white" alt="Author">
  <img src="https://img.shields.io/badge/License-MIT-green.svg?style=flat&logo=opensourceinitiative&logoColor=white" alt="License">
  <img src="https://img.shields.io/badge/Platform-Linux%20%2F%20Unix-orange.svg?style=flat&logo=linux&logoColor=white" alt="Platform">
  <img src="https://img.shields.io/badge/Version-1.0.0-blue?style=flat&logo=semver&logoColor=white" alt="Version">
</p>

---

## Autor

* **Manuel Sadi Kufika**

---

## Sobre a Ferramenta

A **BANKAI** é uma ferramenta de auditoria de segurança orientada a desempenho, construída de raiz em linguagem **C**. Inspirada na robustez de ferramentas clássicas de cibersegurança, a BANKAI adota uma **arquitetura estritamente modular**, separando o escaneamento de portas, a auditoria sem fios (`libpcap`), a exportação de dados estruturados e a gestão dinâmica de argumentos de linha de comandos.

---

## Funcionalidades Principais

* **Scanner de Portas TCP Multi-threaded:** Varrimento rápido de portas utilizando sockets de baixo nível e gestão de threads (`pthread`) para máxima eficiência.
* **Auditoria de Redes Wi-Fi (Beacon Sniffing):** Captura e análise de pacotes de gestão sem fios através da biblioteca `libpcap` em placas configuradas em modo de monitorização.
* **Deteção Avançada de Segurança:** Identificação automática do tipo de encriptação das redes Wi-Fi próximas, distinguindo redes clássicas **WPA2-AES** de redes modernas **WPA3-Personal (SAE)**.
* **Exportação JSON Nativa:** Registo automático de todos os resultados (portas abertas, SSIDs, canais e protocolos de segurança) em relatórios estruturados em formato JSON para automação.

---

## Estrutura do Projeto

```text
bankai/
├── include/
│   ├── bankai.h          # Definições globais
│   ├── exporter.h        # Protótipos do módulo de exportação JSON
│   ├── port_scanner.h    # Protótipos do scanner de portas
│   └── wifi_audit.h      # Protótipos da auditoria Wi-Fi
├── src/
│   ├── main.c            # Ponto de entrada e parser de argumentos (getopt)
│   ├── port_scanner.c    # Implementação do Port Scanner multi-threaded
│   ├── wifi_audit.c      # Implementação do Packet Sniffer e parser de IEs
│   └── exporter.c        # Gestão de escrita de relatórios JSON
└── Makefile              # Automação de compilação

```

---

## Requisitos e Dependências

Para compilar e executar a BANKAI num sistema Linux (Ubuntu/Debian/Kali Linux), necessitas de:

* Compilador GCC
* Make
* Biblioteca `libpcap` (desenvolvimento)
* Threads POSIX (`pthread`)

Podes instalar as dependências no Debian/Ubuntu com o seguinte comando:

```bash
sudo apt update
sudo apt install build-essential libpcap-dev

```

---

## Instalação e Compilação

1. Clona o repositório para a tua máquina:
```bash
git clone [https://github.com/O_TEU_UTILIZADOR/bankai.git](https://github.com/O_TEU_UTILIZADOR/bankai.git)
cd bankai

```


2. Compila o projeto utilizando o Makefile:
```bash
make

```



Esta operação irá gerar o executável binário `bankai` na pasta raiz.

---

## Como Utilizar

Executa o comando de ajuda para visualizar todas as opções e modos disponíveis:

```bash
./bankai -h

```

### 1. Executar Port Scanner TCP

Para varrer as portas padrão (1 a 1024) num alvo autorizado e exportar os resultados para um ficheiro JSON customizado:

```bash
sudo ./bankai -m port -t 192.168.1.1 -o resultados_portas.json

```

### 2. Executar Auditoria Wi-Fi (Beacon Frames)

*Nota: Requer que a placa de rede sem fios esteja configurada previamente em modo de monitorização (ex: `wlan0mon`).*

```bash
sudo ./bankai -m wifi -i wlan0mon -o relatorio_wifi.json

```

---

## Exemplo de Relatório JSON Gerado

Os relatórios são salvos num formato estruturado para integração em ferramentas externas:

```json
[
  {
    "tool": "BANKAI",
    "type": "port_scan",
    "target": "127.0.0.1",
    "port": 80,
    "status": "open"
  },
  {
    "tool": "BANKAI",
    "type": "wifi_audit",
    "ssid": "Rede_Empresa_Secure",
    "security": "WPA3-Personal (SAE)",
    "channel": 6
  },
  {}
]

```

---

## Aviso Legal (Disclaimer)

> O desenvolvimento da ferramenta **BANKAI** tem fins estritamente educacionais, de investigação académica e de testes de intrusão autorizados. O autor não assume qualquer responsabilidade por utilizações indevidas, danos causados a sistemas de terceiros ou infrações legais decorrentes do uso deste software. Utiliza apenas em redes e sistemas sobre os quais possuas permissão expressa.

---

## Licença

Este projeto está distribuído sob a licença [MIT](https://www.google.com/search?q=LICENSE). Podes consultar o ficheiro de licença para mais detalhes.

```

```