#include <malloc.h>
#include<stdio.h>

typedef struct {
	unsigned int nr;
	char* pacient;
	char* medic;
	char* statut;
	unsigned char nrMedicamente;
	float procentCompensare;
}reteta;

typedef struct {
	reteta info;
	struct nodld* next, * prev;
}nodld;

nodld* inserareNod(nodld* cap, nodld** coada, reteta r)
{
	nodld* nou = (nodld*)malloc(sizeof(nodld));
	nou->info.nr = r.nr;
	nou->info.pacient = (char*)malloc((strlen(r.pacient) + 1) * sizeof(char));
	strcpy(nou->info.pacient, r.pacient);
	nou->info.medic = (char*)malloc((strlen(r.medic) + 1) * sizeof(char));
	strcpy(nou->info.medic, r.medic);
	nou->info.statut = (char*)malloc((strlen(r.statut) + 1) * sizeof(char));
	strcpy(nou->info.statut, r.statut);
	nou->info.nrMedicamente = r.nrMedicamente;
	nou->info.procentCompensare = r.procentCompensare;

	nou->next = NULL;
	nou->prev = NULL;
	if (cap == NULL)
	{
		cap = nou;
		*coada = nou;
	}
	else
	{
		nodld* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		(*coada) = nou;
	}
	return cap;
}

void afisareLD(nodld* cap) {
	nodld* temp = cap;
	while (temp->next)
	{
		printf("\n numar reteta: %u, nume pacient: %s, nume medic: %s, statut special: %s, numar medicamente: %hhu, procent compensare: %5.2f",
			temp->info.nr, temp->info.pacient, temp->info.medic, temp->info.statut, temp->info.nrMedicamente, temp->info.procentCompensare);
		temp = temp->next;
	}
	printf("\n numar reteta: %u, nume pacient: %s, nume medic: %s, statut special: %s, numar medicamente: %hhu, procent compensare: %5.2f",
		temp->info.nr, temp->info.pacient, temp->info.medic, temp->info.statut, temp->info.nrMedicamente, temp->info.procentCompensare);

}

void afisareInversaLD(nodld* coada) {
	nodld* temp = coada;
	while (temp->prev)
	{
		printf("\n numar reteta: %u, nume pacient: %s, nume medic: %s, statut special: %s, numar medicamente: %hhu, procent compensare: %5.2f",
			temp->info.nr, temp->info.pacient, temp->info.medic, temp->info.statut, temp->info.nrMedicamente, temp->info.procentCompensare);
		temp = temp->prev;
	}
	printf("\n numar reteta: %u, nume pacient: %s, nume medic: %s, statut special: %s, numar medicamente: %hhu, procent compensare: %5.2f",
		temp->info.nr, temp->info.pacient, temp->info.medic, temp->info.statut, temp->info.nrMedicamente, temp->info.procentCompensare);

}

void dezalocareLD(nodld* cap)
{
	nodld* temp = cap;
	while (temp)
	{
		nodld* temp2 = temp->next;
		free(temp->info.medic);
		free(temp->info.pacient);
		free(temp->info.statut);
		free(temp);
		temp = temp2;
	}
}

void stergere(nodld** cap, nodld** coada, unsigned char prag) {
	if ((*cap)->info.nrMedicamente < prag)
	{
		nodld* temp = *cap;
		(*cap) = (*cap)->next;
		if (*cap != NULL)
			(*cap)->prev = NULL;
		free(temp->info.medic);
		free(temp->info.pacient);
		free(temp->info.statut);
		free(temp);
		return;
	}
	else
		if ((*coada)->info.nrMedicamente < prag)
		{
			nodld* temp = *coada;
			(*coada) = (*coada)->prev;
			if (*coada != NULL)
				(*coada)->next = NULL;
			free(temp->info.medic);
			free(temp->info.pacient);
			free(temp->info.statut);
			free(temp);
			return;
		}
		else
		{
			nodld* temp = *cap;
			while (temp)
			{
				if (temp->info.nrMedicamente < prag)
				{
					nodld* anterior = temp->prev;
					nodld* urmator = temp->next;
					anterior->next = urmator;
					urmator->prev = anterior;
					free(temp->info.medic);
					free(temp->info.pacient);
					free(temp->info.statut);
					free(temp);
					return;
				}
				temp = temp->next;
			}
		}
}

void stergereMultipla(nodld** cap, nodld** coada, unsigned char prag) {
	nodld* temp = *cap;
	int contor = 1;
	while (contor)
	{
		nodld* urmator = temp->next;
		if (temp->info.nrMedicamente < prag)
		{
			if (temp == temp->next)
			{
				free(temp->info.medic);
				free(temp->info.pacient);
				free(temp->info.statut);
				free(temp);
				*cap = NULL;
				*coada = NULL;
				return;
			}
			else
			{
				nodld* Nodanterior = temp->prev;
				nodld* Nodurmator = temp->next;
				if (Nodanterior)
					Nodanterior->next = Nodurmator;
				if (Nodurmator)
					Nodurmator->prev = Nodanterior;

				if (temp == *cap)
				{
					*cap = temp->next;
					if (*cap != NULL)
						(*cap)->prev = NULL;
				}
				if (temp == *coada)
				{
					*coada = temp->prev;
					if (*coada != NULL)
						(*coada)->next = NULL;
				}
				free(temp->info.medic);
				free(temp->info.pacient);
				free(temp->info.statut);
				free(temp);

			}
		}
		temp = urmator;
		if (temp->next == NULL)
			contor = 0;
	}
}

void main()
{
	nodld* cap = NULL, * coada = NULL;
	reteta r;
	int nrElem;
	char buffer[60];
	FILE* f = fopen("txt.txt", "r");
	fscanf(f, "%d", &nrElem);
	for (int i = 0; i < nrElem; i++)
	{
		fscanf(f, "%u", &r.nr);
		fscanf(f, "%s", buffer);
		r.pacient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(r.pacient, buffer);

		fscanf(f, "%s", buffer);
		r.medic = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(r.medic, buffer);

		fscanf(f, "%s", buffer);
		r.statut = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(r.statut, buffer);

		fscanf(f, "%u", &r.nrMedicamente);
		fscanf(f, "%f", &r.procentCompensare);

		cap = inserareNod(cap, &coada, r);
		free(r.medic);
		free(r.pacient);
		free(r.statut);
	}
	fclose(f);

	printf("\n\n afisare lisat dubla \n\n");
	afisareLD(cap);

	printf("\n\n afisare inversa lisat dubla \n\n");
	afisareInversaLD(coada);

	//printf("\n\n cerinta 4 - fct stergere doar o linie \n\n");
	//stergere(&cap, &coada,2 );
	//afisareLD(cap);

	printf("\n\n cerinta 4 - fct stergere MULTIPLA \n\n");
	stergereMultipla(&cap, &coada, 3);
	afisareLD(cap);

	dezalocareLD(cap);
}