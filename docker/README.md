# Ubuntu 24.04 LTS in Docker (v3.0)


## Prerequisites

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


## Getting ssdd-docker

```bash
git clone https://github.com/acaldero/uc3m_sd.git
cd uc3m_sd
./docker.sh build
```


## Using ssdd-docker

<html>
 <table>
  <tr>
  <th>Summary</th>
  <th>Example of work session</th>
  </tr>
  <tr>
  <td>
</html>

  * First time + "each time u20-dockerfile is updated":
    * ./docker.sh build

  * To start **3** containers:
    *  ./docker.sh start **3**

  * To get into container **2**:
    *  ./docker.sh bash **2**

  * Being within **2**, to exit:
    *  exit

  * To stop the containers:
    *  ./docker.sh stop

  * Available options for debugging:
    *  ./docker.sh status
    *  ./docker.sh network

<html>
  </td>
  <td>
</html>

  * To start:
    * To start a work session with **2** containers, please execute:
      *  ./docker.sh start **2**
    * To check the containers are running please use:
      *  ./docker.sh status
    * To get the containers internal IP address please use:
      *  ./docker.sh network

  * To work with some container:
    * To get into container **1** out of 2 please execute:
      *  ./docker.sh bash **1**
    * <some work inside container **1** at /work directory>
    * To exit from container **1** please use:
      *  exit

  * To stop:
    * To stop the work session please use:
      *  ./docker.sh stop

<html>
  </td>
  </tr>
 </table>
</html>


**Please beware of**:
  * Any modification outside /shared will be discarded on container stopping.
  * Please make a backup of your work "frequently".
  * You might need to use "sudo" before ./docker.sh if your user doesn't belong to the docker group (could be solved by using "sudo usermod -aG docker ${USER}")


## Example using ssdd-docker

![Example of using 2 containers in Linux, and using each one with netcat](u20-example1.gif)

