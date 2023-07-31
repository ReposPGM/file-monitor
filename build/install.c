#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void createFile();
void refreshEnv();

int main()
{
    const char *choco = "powershell -Command \"Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))\"";
    system(choco);

    refreshEnv();

    const char *gcc = "choco install mingw";
    system(gcc);

    const char *curl = "choco install curl -y";
    system(curl);

    const char *php = "choco install php -y";
    system(php);

    const char *composer = "choco install composer -y";
    system(composer);

    const char *git = "choco install git -y";
    system(git);

    refreshEnv();

    const char *get_project = "git clone https://github.com/ReposPGM/file-monitor.git";
    system(get_project);

    if (chdir("./file-monitor") != 0)
    {
        printf("Fallo al cambior de directorio.\n");
    }

    const char *composer_install = "composer install";
    system(composer_install);

    createFile();

    printf("Proyecto instalado");

    return 0;
}

void createFile()
{
    char path[200];
    char api[200];

    char contact_path[250];
    char contact_api[250];

    FILE *file;

    file = fopen(".env", "w");

    if (file == NULL)
    {
        printf("Error al crear el archivo .env \n");
    }

    printf("\n Introduce la ruta completa hacia la carpeta donde se subiran los archivos: ");
    fgets(path, sizeof(path), stdin);

    printf("\n Introduce la api donde se subiran los archivos: ");
    fgets(api, sizeof(api), stdin);

    sprintf(contact_path, "PATH_FILES=\"%s\"", path);
    sprintf(contact_api, "\nAPI_URL=\"%s\"", api);

    fprintf(file, contact_path);
    fprintf(file, contact_api);

    fclose(file);
}

void refreshEnv()
{
    putenv("REFRESH_VARIABLE=1");
    putenv("REFRESH_VARIABLE=");
}
