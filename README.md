<h1 align="center">BANKAI</h1>

<p align="center">
  <b>Framework modular de auditoria de rede e segurança, de alta performance, desenvolvida em C.</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-00599C?style=flat&logo=c&logoColor=white" alt="Linguagem C">
  <img src="https://img.shields.io/badge/Platform-Linux%20%2F%20Unix-orange?style=flat&logo=linux&logoColor=white" alt="Plataforma Linux/Unix">
  <img src="https://img.shields.io/badge/Version-1.0.0-blue?style=flat&logo=semver&logoColor=white" alt="Versão 1.0.0">
  <img src="https://img.shields.io/badge/License-MIT-green?style=flat&logo=opensourceinitiative&logoColor=white" alt="Licença MIT">
  <img src="https://img.shields.io/badge/Author-Manuel%20Sadi%20Kufika-blueviolet?style=flat&logo=github&logoColor=white" alt="Autor">
</p>

<p align="center">
  <a href="#sobre">Sobre</a> •
  <a href="#funcionalidades">Funcionalidades</a> •
  <a href="#instalação">Instalação</a> •
  <a href="#utilização">Utilização</a> •
  <a href="#formato-de-saída-json">Saída JSON</a> •
  <a href="#estrutura-do-projeto">Estrutura</a> •
  <a href="#aviso-legal">Aviso Legal</a>
</p>

---

## Sobre

A **BANKAI** é uma ferramenta de auditoria de segurança orientada a desempenho, construída de raiz em **C**. Inspirada na robustez das ferramentas clássicas de cibersegurança, adota uma **arquitetura estritamente modular**, que separa de forma clara:

| Módulo | Responsabilidade |
|---|---|
| **Port Scanner** | Varrimento de portas TCP com múltiplas threads |
| **Wi-Fi Audit** | Captura e análise de pacotes de gestão sem fios (`libpcap`) |
| **Exporter** | Exportação de resultados estruturados em JSON |
| **CLI** | Gestão dinâmica de argumentos de linha de comandos (`getopt`) |

---

## Funcionalidades

- **Scanner de portas TCP multi-threaded** — varrimento rápido com sockets de baixo nível e gestão de threads POSIX (`pthread`).
- **Auditoria de redes Wi-Fi (beacon sniffing)** — captura e análise de frames de gestão com `libpcap`, usando placas em modo de monitorização.
- **Deteção avançada de segurança** — identifica automaticamente o tipo de encriptação das redes próximas, distinguindo **WPA2-AES** de **WPA3-Personal (SAE)**.
- **Exportação JSON nativa** — regista portas abertas, SSIDs, canais e protocolos de segurança em relatórios estruturados, prontos para automação e integração com outras ferramentas.

---

## Requisitos

| Requisito | Descrição |
|---|---|
| Sistema operativo | Linux (testado em Ubuntu, Debian e Kali Linux) |
| Compilador | GCC |
| Automação | Make |
| Bibliotecas | `libpcap` (pacote de desenvolvimento) e POSIX Threads (`pthread`) |
| Hardware (modo Wi-Fi) | Placa de rede sem fios com suporte a modo de monitorização |

Instalação das dependências em Debian/Ubuntu/Kali:

```bash
sudo apt update
sudo apt install build-essential libpcap-dev
```

---

## Instalação

**1. Clonar o repositório**

```bash
git clone https://github.com/O_TEU_UTILIZADOR/bankai.git
cd bankai
```

**2. Compilar**

```bash
make
```

O executável `bankai` será gerado na raiz do projeto.

---

## Utilização

Para consultar todas as opções e modos disponíveis:

```bash
./bankai -h
```

### Opções

| Opção | Descrição |
|---|---|
| `-m <modo>` | Modo de operação: `port` (scanner de portas) ou `wifi` (auditoria Wi-Fi) |
| `-t <alvo>` | Endereço IP do alvo (modo `port`) |
| `-i <interface>` | Interface de rede em modo de monitorização (modo `wifi`) |
| `-o <ficheiro>` | Ficheiro JSON de saída |
| `-h` | Mostra a ajuda |

### Modo 1 — Port Scanner TCP

Varre as portas padrão (1 a 1024) de um alvo autorizado e exporta os resultados para JSON:

```bash
sudo ./bankai -m port -t 192.168.1.1 -o resultados_portas.json
```

### Modo 2 — Auditoria Wi-Fi (Beacon Frames)

> **Pré-requisito:** a placa sem fios deve estar previamente configurada em modo de monitorização (ex.: `wlan0mon`).

```bash
sudo ./bankai -m wifi -i wlan0mon -o relatorio_wifi.json
```

---

## Formato de Saída JSON

Os relatórios são guardados num formato estruturado, adequado a integração com ferramentas externas:

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
  }
]
```

| Campo | Tipo | Descrição |
|---|---|---|
| `tool` | string | Nome da ferramenta (`BANKAI`) |
| `type` | string | Tipo de registo: `port_scan` ou `wifi_audit` |
| `target` | string | Alvo analisado (registos `port_scan`) |
| `port` | inteiro | Porta TCP detetada (registos `port_scan`) |
| `status` | string | Estado da porta, p. ex. `open` |
| `ssid` | string | Nome da rede (registos `wifi_audit`) |
| `security` | string | Protocolo de segurança, p. ex. `WPA2-AES` ou `WPA3-Personal (SAE)` |
| `channel` | inteiro | Canal Wi-Fi (registos `wifi_audit`) |

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
│   ├── port_scanner.c    # Port Scanner multi-threaded
│   ├── wifi_audit.c      # Packet sniffer e parser de Information Elements (IEs)
│   └── exporter.c        # Escrita de relatórios JSON
└── Makefile              # Automação de compilação
```

---

## Aviso Legal

> **A BANKAI destina-se exclusivamente a fins educacionais, de investigação académica e de testes de intrusão autorizados.**
>
> O autor não assume qualquer responsabilidade por utilizações indevidas, danos causados a sistemas de terceiros ou infrações legais decorrentes do uso deste software. Utiliza-a apenas em redes e sistemas sobre os quais possuas **permissão expressa e por escrito**.

---

## Licença

Distribuído sob a licença **MIT**. Consulta o ficheiro [LICENSE](LICENSE) para mais detalhes.

---

## Autor

**Manuel Sadi Kufika**
