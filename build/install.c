#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void createEnv();
void replace_backslash();

int main()
{
    const char *choco = "powershell -Command \"Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))\"";
    system(choco);

    const char *curl = "C:\\ProgramData\\chocolatey\\choco install curl -y";
    system(curl);

    const char *php = "C:\\ProgramData\\chocolatey\\choco install php -y";
    system(php);

    const char *composer = "C:\\ProgramData\\chocolatey\\choco install composer -y";
    system(composer);

    const char *git = "C:\\ProgramData\\chocolatey\\choco install git -y";
    system(git);

    const char *get_project = "git clone https://github.com/ReposPGM/file-monitor.git";
    system(get_project);

    if (chdir("./file-monitor") != 0)
    {
        printf("Fallo al cambior de directorio.\n");
    }

    const char *composer_install = "composer install";
    system(composer_install);

    createEnv();

    printf("\n Proyecto instalado");

    printf("\n Presione 'Enter' para cerrar el programa...");
    getchar();

    return 0;
}

void createEnv()
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
    path[strcspn(path, "\n")] = 0;

    printf("\n Introduce la api donde se subiran los archivos: ");
    fgets(api, sizeof(api), stdin);
    api[strcspn(api, "\n")] = 0;

    replace_backslash(path);

    sprintf(contact_path, "PATH_FILES=\"%s\"", path);
    sprintf(contact_api, "\nAPI_URL=\"%s\"", api);

    fprintf(file, contact_path);
    fprintf(file, contact_api);

    fclose(file);
}

void replace_backslash(char* str) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '\\') {
            str[i] = '/';
        }
    }
}