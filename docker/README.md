# Ubuntu 24.04 LTS en Docker (v3.0)


## Pre-requisitos

* Windows:
  * Windows Terminal: https://apps.microsoft.com/detail/9n0dx20hk701?hl=es-ES&gl=ES
  * WSL: https://docs.docker.com/desktop/setup/install/windows-install/#wsl-verification-and-setup
  * Docker desktop: https://docs.docker.com/desktop/setup/install/windows-install/
* MacOS:
  * Docker desktop: https://docs.docker.com/desktop/setup/install/mac-install/
* Linux:
  * Docker: https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository
    <details>
    <summary>De forma abreviada para Linux/Ubuntu ... (hacer click)</summary>
   
    ```bash
    : Add Docker's official GPG key:
    sudo apt update
    sudo apt install ca-certificates curl
    sudo install -m 0755 -d /etc/apt/keyrings
    sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
    sudo chmod a+r /etc/apt/keyrings/docker.asc

    : Add the repository to Apt sources:
    sudo tee /etc/apt/sources.list.d/docker.sources <<EOF
    Types: deb
    URIs: https://download.docker.com/linux/ubuntu
    Suites: $(. /etc/os-release && echo "${UBUNTU_CODENAME:-$VERSION_CODENAME}")
    Components: stable
    Signed-By: /etc/apt/keyrings/docker.asc
    EOF

    : Update repo and install docker
    sudo apt update
    sudo apt install docker-ce docker-ce-cli containerd.io \
                     docker-buildx-plugin docker-compose-plugin -y
    ```
  </details>


## Obtener ssdd-docker

```bash
git clone https://github.com/acaldero/uc3m_sd.git
cd uc3m_sd
./docker.sh build
```


## Usar ssdd-docker

<html>
 <table>
  <tr>
  <th>Resumen</th>
  <th>Ejemplo de sesión de trabajo</th>
  </tr>
  <tr>
  <td>
</html>

  * Primera vez + "cada vez que se actualiza dockerfile":
    * ./docker.sh build

  * Para arrancar **3** contenedores:
    *  ./docker.sh start **3**

  * Para entrar en el contenedor **2**:
    *  ./docker.sh bash **2**

  * Estando en **2**, para salir:
    *  exit

  * Para parar los contenedores:
    *  ./docker.sh stop

  * Opciones disponibles para depuración:
    *  ./docker.sh status
    *  ./docker.sh network

<html>
  </td>
  <td>
</html>

  * Para arrancar:
    * To start a work session with **2** contenedores, please execute:
      *  ./docker.sh start **2**
    * To check the contenedores are running please use:
      *  ./docker.sh status
    * To get the contenedores internal IP address please use:
      *  ./docker.sh network

  * Para trabajar con algún contenedor:
    * Para trabajar dentro del contenedor **1** de 2 por favor ejecute:
      *  ./docker.sh bash **1**
    * <some work inside container **1** at /work directory>
    * Para salir del contenedor **1** por favor ejecute:
      *  exit

  * Para parar:
    * Para parar la sesión de trabajo por favor ejecute:
      *  ./docker.sh stop

<html>
  </td>
  </tr>
 </table>
</html>


**Por favor tenga en cuenta que**:
  * Cualquier modificación fuera de "/shared" se perderá cuando se pare los contenedores.
  * Por favor haga copia de seguridad de su trabajo "con suficiente frecuencia".
  * Puede que necesite usar "sudo" antes de ./docker.sh si su usuario/a no pertenece al grupo de docker (se puede solventar usando ```sudo usermod -aG docker ${USER}```)


## Ejemplo de uso de ssdd-docker

![Ejemplo de uso de 2 contenedores en Linux, y comunicar ambos con netcat](u20-example1.gif)

