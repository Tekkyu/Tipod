#include "mbed.h"
#include "stdio.h"
#include "emetteur.h"
Serial pc(USBTX,USBRX);
DigitalOut myledR(PTB22);
DigitalOut myledG(PTE26);



char datatest [30];
char *message;
Emetteur kim;
int main()
{
    char chaine_PWR[]="1500"; // definition de la puissance d'emission
    char chaine_BAND[]="B1"; // definition de la bande d'emission
    char chaine_FRQ[]="300"; // definition de la bande d'emission
    char chaine[30];
    char trame[30];
    char testdec3tohex=kim.dec3tohex(9,trame);
    if (testdec3tohex==0) pc.printf("trame convertie correctement, resultalt : %x%x%x \n",trame[0],trame[1],trame[2]);
    else pc.printf(" erreur %d \n",testdec3tohex);
    //char trame[]=datatest; // 208
    RetStatusKIMTypeDef test;
    unsigned int k=0;
    myledR = 1; // led D3 eteinte
    myledG = 1; // led D3 eteinte

    pc.printf("Programme lance \n");
    // Mise en marche module KIM
    if (kim.set_sleepMode(false)) pc.printf("Module power OK \n");
    else pc.printf("Module power failed \n");
    // Reglage puissance module KIM
    pc.printf("Reglage puissance : %s mW \n",chaine_PWR);
    uint8_t n=sprintf(chaine,"%s",chaine_PWR);
    if (kim.set_PWR(chaine,n)!= OK_KIM) printf("erreur configuration puissance \n");
    // Reglage bande module KIM
    pc.printf("Reglage Bande : %s \n",chaine_BAND);
    n=sprintf(chaine,"%s",chaine_BAND);
    if (kim.set_BAND(chaine,n)!= OK_KIM) printf("erreur configuration bande \n");
    // Reglage frequence module KIM
    pc.printf("Reglage frequence : %s \n",chaine_FRQ);
    n=sprintf(chaine,"%s",chaine_FRQ);
    if (kim.set_FRQ(chaine,n)!= OK_KIM) printf("erreur configuration frequence \n");

    // Affichage des caracteristiques du module KIM
    pc.printf("caracteristiques module KIM : \n");
    wait(0.5);
    message=kim.get_ID(); // lecture de l'ID
    pc.printf("%s",message);
    wait(0.5);
    message=kim.get_SN(); // lecture du Serial Number
    pc.printf("%s",message);
    wait(0.5);
    message=kim.get_FW(); // lecture de la version du firmware
    pc.printf("%s",message);
    wait(0.5);
    message=kim.get_PWR(); // lecture de la puissance d'emission
    pc.printf("%s",message);
    wait(0.5);
    message=kim.get_BAND(); // lecture de la bande d'emission
    pc.printf("%s",message);
    wait(0.5);
    message=kim.get_FRQ(); // lecture de l'offset de frequence
    pc.printf("%s",message);
    wait(0.5);
    message=kim.get_TCXOWU(); // lecture du temps TCXO
    pc.printf("%s",message);
    myledR = 0; // led D3 allumée
    wait(1);
    //test=kim.send_data("0102030405",10);
    test=kim.send_data(trame,3);
    //pc.printf("%c%c%c \n",tab[0],tab[1],tab[2]);
    pc.printf("data envoye : %c%c%c \n",trame[0],trame[1],trame[2]);
    if (test!=1) {
    pc.printf("echec %d envoi message \n",test);
    myledR = 0;// led Rouge allumée
    myledG = 1; // led Verte eteinte
    wait(5);
    }
    else {
    pc.printf("Envoi message OK \n");
    myledG = 0; // led Verte allumée
    myledR = 1; // led Rouge eteinte
    wait(5);
    }
    myledR = 1; // led Rouge eteinte
    myledG = 1; // led Verte eteinte  
    if (kim.set_sleepMode(true)) pc.printf("Module power OFF OK \n"); // extinction du module
    else pc.printf("Module power OFF failed \n");
    wait(10);
    while(1) {
    myledR = 1; // led Rouge eteinte
    myledG = 1; // led Verte eteinte  
        pc.printf("on allume KIM\n");
        if (kim.set_sleepMode(false)==1) pc.printf("Module power ON \n"); // activation du module
        else pc.printf("Module power ON failed \n");
        //char n=sprintf(chaine,"%x",k);
        pc.printf("on envoie message KIM\n");
        test=kim.send_data(trame,3);
        if (test!= 1){ 
        pc.printf("echec %x envoi message : %s\n",test,trame);
            myledR = 0;// led Rouge allumée
            myledG = 1; // led Verte eteinte
    wait(5);
        }
        else 
        {
        pc.printf("Envoi message OK : %s \n",test,chaine); 
        myledG = 0; // led Verte allumée
        myledR = 1; // led Rouge eteinte
        wait(5);
        }
        k++;
        wait(1);
        pc.printf("on eteint KIM\n");
        myledR = 1; // led Rouge eteinte
        myledG = 1; // led Verte eteinte  
        if (kim.set_sleepMode(true)) pc.printf("Module power OFF OK \n"); // extinction du module
        else pc.printf("Module power OFF failed \n");
        wait(10);
    }
}
