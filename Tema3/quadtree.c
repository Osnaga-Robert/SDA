#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} culori;

typedef struct nod
{
    culori culoare;
    struct nod *ss, *s, *d, *dd;
} nod, *Nod;

typedef struct QuadtreeNode
{
    unsigned char blue, green, red;
    uint32_t area;
    int32_t top_left, top_right;
    int32_t bottom_left, bottom_right;
} QuadtreeNode;

Nod initializare()
{
    Nod temp = malloc(sizeof(struct nod));
    temp->d = temp->dd = temp->ss = temp->s = NULL;
    temp->culoare.blue = 0;
    temp->culoare.green = 0;
    temp->culoare.red = 0;
    return temp;
}

void split(Nod arbore, culori **matrice, int x1, int x2, int y1, int y2, int prag, int *nr_noduri, int *nr_culori)
{
    long long red = 0, green = 0, blue = 0, mean = 0;
    int i, j;
    *nr_noduri = *nr_noduri + 1;
    long long size = (x2 - x1) * (y2 - y1);

    for (i = x1; i < x2; i++)
    {
        for (j = y1; j < y2; j++)
        {
            red += matrice[i][j].red;
            green += matrice[i][j].green;
            blue += matrice[i][j].blue;
        }
    }
    red /= size;
    green /= size;
    blue /= size;

    for (i = x1; i < x2; i++)
    {
        for (j = y1; j < y2; j++)
        {
            mean += (red - matrice[i][j].red) * (red - matrice[i][j].red) + (green - matrice[i][j].green) * (green - matrice[i][j].green) + (blue - matrice[i][j].blue) * (blue - matrice[i][j].blue);
        }
    }
    arbore->culoare.red = red;
    arbore->culoare.green = green;
    arbore->culoare.blue = blue;
    mean = mean / (3 * size);
    if (mean > prag)
    {
        arbore->ss = initializare();
        arbore->s = initializare();
        arbore->d = initializare();
        arbore->dd = initializare();
        split(arbore->ss, matrice, x1, (x1 + x2) / 2, y1, (y1 + y2) / 2, prag, nr_noduri, nr_culori);
        split(arbore->s, matrice, x1, (x1 + x2) / 2, (y1 + y2) / 2, y2, prag, nr_noduri, nr_culori);
        split(arbore->d, matrice, (x1 + x2) / 2, x2, (y1 + y2) / 2, y2, prag, nr_noduri, nr_culori);
        split(arbore->dd, matrice, (x1 + x2) / 2, x2, y1, (y1 + y2) / 2, prag, nr_noduri, nr_culori);
    }
    else
    {
        *nr_culori = *nr_culori + 1;
    }
}

void tree_To_Grid(culori **grid, Nod root, int i1, int i2, int j1, int j2)
{

    int i, j;
    // completeaza valorile pixelilor corespunzatori blocului
    for (i = i1; i < i2; i++)
        for (j = j1; j < j2; j++)
        {
            grid[i][j].red = root->culoare.red;
            grid[i][j].green = root->culoare.green;
            grid[i][j].blue = root->culoare.blue;
        }
    if (root->ss != NULL)
    { // apeleaza functia pentru fii sai
        tree_To_Grid(grid, root->ss, i1, (i2 + i1) / 2, j1, (j2 + j1) / 2);
        tree_To_Grid(grid, root->s, i1, (i2 + i1) / 2, (j2 + j1) / 2, j2);
        tree_To_Grid(grid, root->d, (i2 + i1) / 2, i2, (j2 + j1) / 2, j2);
        tree_To_Grid(grid, root->dd, (i2 + i1) / 2, i2, j1, (j2 + j1) / 2);
    }
}

void Vector(Nod arbore, QuadtreeNode *vector, int size, int *index)
{

    int aux = *index;
    vector[aux].area = size;
    vector[aux].red = arbore->culoare.red;
    vector[aux].green = arbore->culoare.green;
    vector[aux].blue = arbore->culoare.blue;
    if (arbore->ss != NULL)
    {
        int up = *index;
        (*index)++;
        vector[up].top_left = *(index);
        Vector(arbore->ss, vector, size / 4, index);
        (*index)++;
        vector[up].top_right = *(index);
        Vector(arbore->s, vector, size / 4, index);
        (*index)++;
        vector[aux].bottom_right = *(index);
        Vector(arbore->d, vector, size / 4, index);
        (*index)++;
        vector[aux].bottom_left = *(index);
        Vector(arbore->dd, vector, size / 4, index);
    }
    else
    {
        vector[aux].top_left = -1;
        vector[aux].top_right = -1;
        vector[aux].bottom_right = -1;
        vector[aux].bottom_left = -1;
    }
}

Nod horizontal_m(Nod root)
{

    Nod keep = root;
    if (root->ss != NULL)
    { // daca nu e nod frunza
        // se interschimba blocul din stanga sus cu cel din dreapta sus
        Nod aux = root->ss;
        root->ss = root->s;
        root->s = aux;
        // se interschimba blocul din stanga jos cu cel din dreapta jos
        aux = root->d;
        root->d = root->dd;
        root->dd = aux;
        // apeleaza functia pentru fii
        root->ss = horizontal_m(root->ss);
        root->s = horizontal_m(root->s);
        root->d = horizontal_m(root->d);
        root->dd = horizontal_m(root->dd);
    }
    return keep;
}

Nod vertical_m(Nod root)
{

    Nod keep = root;
    if (root->ss != NULL)
    { // daca nu e nod frunza
        // se interschimba blocul din stanga sus cu cel din stanga jos
        Nod aux = root->ss;
        root->ss = root->dd;
        root->dd = aux;
        // se interschimba blocul din dreapta sus cu cel din dreapta jos
        aux = root->s;
        root->s = root->d;
        root->d = aux;
        // apeleaza functia pentru fii
        root->ss = vertical_m(root->ss);
        root->s = vertical_m(root->s);
        root->d = vertical_m(root->d);
        root->dd = vertical_m(root->d);
    }
    return keep;
}

int main(int argc, char *argv[])
{
    int factor, type, i, j, putere = 0, aux, a, b, c, d, e, f, noduri = 0;
    int nr_culori = 0;
    Nod arbore = NULL;
    int pas = 0;
    int cnt = 0;
    arbore = initializare();
    char tip[3];
    char buffer[15], *tkn;
    char delimiters[3] = " \n\0";
    int lungime, latime, len;
    QuadtreeNode *v = NULL;
    culori **RGB;
    FILE *input;
    if (!strcmp(argv[1], "-c"))
    {
        factor = atoi(argv[2]);
        input = fopen(argv[3], "rb");
        fread(buffer, sizeof(buffer), 1, input);
        tkn = strtok(buffer, delimiters);
        tkn = strtok(NULL, delimiters);
        lungime = atoi(tkn);
        tkn = strtok(NULL, delimiters);
        latime = atoi(tkn);
        RGB = (culori **)malloc(lungime * sizeof(culori *));
        for (i = 0; i < lungime; i++)
        {
            RGB[i] = (culori *)malloc(sizeof(culori) * latime);
        }
        for (i = 0; i < lungime; i++)
        {
            for (j = 0; j < latime; j++)
            {
                fread(&RGB[i][j].red, sizeof(unsigned char), 1, input);
                fread(&RGB[i][j].green, sizeof(unsigned char), 1, input);
                fread(&RGB[i][j].blue, sizeof(unsigned char), 1, input);
            }
        }
        split(arbore, RGB, 0, lungime, 0, latime, factor, &noduri, &nr_culori);
        v = malloc(sizeof(QuadtreeNode) * noduri);
        Vector(arbore, v, lungime * latime, &pas);
        FILE *output = fopen(argv[4], "wb");
        fwrite(&nr_culori, sizeof(int), 1, output);
        fwrite(&noduri, sizeof(int), 1, output);
        fwrite(v, sizeof(QuadtreeNode), noduri, output);
        fclose(output);
    }
    if (!strcmp(argv[1], "-d"))
    {
        input = fopen(argv[2], "rb");
        fread(&nr_culori, sizeof(int), 1, input);
        fread(&noduri, sizeof(int), 1, input);
        v = malloc(sizeof(QuadtreeNode) * noduri);
        fread(v, sizeof(QuadtreeNode), noduri, input);
        fclose(input);
        int dim = (int)sqrt(v[0].area);
        RGB = (culori **)malloc(dim * sizeof(culori *));
        for (i = 0; i < dim; i++)
        {
            RGB[i] = (culori *)malloc(dim * sizeof(culori));
        }
    }
    if (!strcmp(argv[1], "-m"))
    {
        printf("DAA")
        if (!strcmp(argv[2], "h"))
            type = 0;
        else
            type = 1;
        factor = atoi(argv[3]);
        input = fopen(argv[4], "rb");
        fread(buffer, sizeof(buffer), 1, input);
        tkn = strtok(buffer, delimiters);
        tkn = strtok(NULL, delimiters);
        lungime = atoi(tkn);
        tkn = strtok(NULL, delimiters);
        latime = atoi(tkn);
        RGB = (culori **)malloc(lungime * sizeof(culori *));
        for (i = 0; i < lungime; i++)
        {
            RGB[i] = (culori *)malloc(sizeof(culori) * latime);
        }
        for (i = 0; i < lungime; i++)
        {
            for (j = 0; j < latime; j++)
            {
                fread(&RGB[i][j].red, sizeof(unsigned char), 1, input);
                fread(&RGB[i][j].green, sizeof(unsigned char), 1, input);
                fread(&RGB[i][j].blue, sizeof(unsigned char), 1, input);
            }
        }
        split(arbore, RGB, 0, lungime, 0, latime, factor, &noduri, &nr_culori);
        printf("%d\n",type);
        if (type == 0){
            printf("DA");
            arbore = horizontal_m(arbore);
        }
        else{
            arbore = vertical_m(arbore);
        }
        tree_To_Grid(RGB, arbore, 0, lungime, 0, latime);
        FILE *fout;
        fout = fopen(argv[5], "wb");
        fprintf(fout, "%s\n%u %u\n%u\n", "P6", lungime, latime, 255);
        for (i = 0; i < lungime; i++)
            fwrite(RGB[i], sizeof(culori), latime, fout);
    }

    return 0;
}