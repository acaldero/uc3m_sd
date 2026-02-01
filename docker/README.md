# Ubuntu 24.04 LTS in Docker (v3.0)

## Getting ssdd-docker

```
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

