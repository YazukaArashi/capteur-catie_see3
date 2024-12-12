#include "mbed.h"
#include "rtos.h"

#define BLINKING_RATE     500ms // Blinking rate in milliseconds

// **********---- TP - Blinky ---------------------------------- //
// -> Modifier l’application pour faire clignoter la LED en utilisant la classe DigitalOut de Mbed OS
/*
int main() {
// Initialiser digital pin LED1 comme une sortie
#ifdef LED1
    DigitalOut led(LED1);
#else
    bool led;
#endif
    printf("Test 1, 2. Test\n");
    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
*/


// **********---- TP - Polling du bouton ----------------------- //
// -> Lire l'état du bouton et l'afficher l'état du bouton sur la sortie standard
// -> Allumer la LED quand le bouton est appuyé, l'éteindre sinon
/*
DigitalOut led(LED1);
DigitalIn button(BUTTON1); // Lecture de l'état du bouton

int main() {
    while (true) {
        int buttonState = button.read()
        printf("Etat du bouton : %d \n", buttonState);
        
        if (buttonState == 0){
            led = 1; // Allume LED si bouton appuyé
        } else {
            led = 0; // Eteint la LED si boutton pas appuyé
        }
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
*/


// **********---- TP - Utiliser une interruption --------------- //
// -> Remplacer la lecture en polling par l'utilisation d'IRQ
/*
DigitalOut led(LED1);
InterruptIn button(BUTTON1);

void flip_on(){
    led = 1; // Allume LED
}
void flip_off(){
    led = 0; // Eteint LED
}

int main()
{
    button.rise(&flip_on); // Lorsque bouton appuyé
    button.fall(&flip_off); // Lorsque bouton relaché
    while (true) 
    {
        printf("Etat du bouton : %d \n", button.read());
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
*/
/* COMMENTAIRE */
/*
La différence entre polling et interruption réside principalement 
dans la manière dont le programme surveille l'état des événements.
Polling : consiste à vérifier en continu l'état d'un périphérique 
ou d'une condition (comme un bouton) dans une boucle active.
Interruption : À l'inverse, une interruption permet de "laisser 
faire" le programme et de ne s'occuper de l'événement que lorsqu'il 
se produit. Lorsqu'un événement se déclenche (comme un appui sur un 
bouton), une interruption interrompt le programme pour exécuter une 
fonction spécifique, puis le programme reprend son cours normal.
*/
// **********---- TP - Ajouter un Timer ------------------------ //
// -> Compter et afficher la durée de l'appui sur le bouton
/*
DigitalOut led(LED1);
InterruptIn button(BUTTON1);

using namespace std::chrono;
Timer t;

void flip_on() {
    led = 1;
}

void flip_off() {
    led = 0;
}

int main() {
    button.rise(&flip_on);
    button.fall(&flip_off);

    while (true) {
        printf("Etat du bouton : %d \n", button.read());

        if (button == 1) {
            t.start();
        }
        else {
            t.stop();
            printf("Bouton relaché - Durée de l'appui du bouton : %llu milliseconds\n", duration_cast<milliseconds>(t.elapsed_time()).count());
            t.reset();
        }
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
*/


// **********---- TP - Controle de la LED par un Ticker -------- //
// -> Faire clignoter la LED à une certaine fréquence, sans boucle infinie
/*
DigitalOut led1(LED1);
DigitalOut led2(LED2);

InterruptIn button(BUTTON1);

using namespace std::chrono;
Timer t;
Ticker flipper;

void flip_on() {
    led1 = 1;
}
void flip_off() {
    led1 = 0;
}
void flip() {
    led2 = !led2;
}

int main()
{
    button.rise(&flip_on);
    button.fall(&flip_off);
    flipper.attach(&flip, 2.0); // Configure le Ticker pour basculer la LED toutes les 2 secondes

    while (true) {
        led1 = !led1;
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
*/
/* COMMENTAIRE */
/*
Le Timer et le Ticker sont deux outils pour gérer le temps, mais 
avec des rôles différents :
Timer : Il mesure une durée spécifique, comme un chronomètre. Il 
démarre, compte le temps écoulé, puis tu peux récupérer ce temps 
pour l'utiliser dans ton programme.
Ticker : Il exécute une fonction à intervalles réguliers, idéal 
pour des actions répétitives comme faire clignoter une LED à une 
fréquence donnée, sans avoir besoin de vérifier constamment.
*/


// **********---- TP - Piloter la frequence de clignotement ---- //
// -> Utiliser le bouton pour changer la fréquence de clignotement à chaque appui
/*
DigitalOut led1(LED1);
DigitalOut led2(LED2);
InterruptIn button(BUTTON1);

using namespace std::chrono;
Timer t;
Ticker flipper;
int cpt = 0, counter = 2;

void flip() {
    cpt = cpt + 1;
    if (cpt == counter) {
        led2 = !led2; //toggle la LED si le compteur et la frequence sont idems.
        cpt = 0; //remise a 0 du compteur. 
    }
}

void change_freq() {
    counter = counter + 1; //diminution de la frequence de clignottement.  
}

int main() {
    button.rise(&change_freq);
    flipper.attach(&flip, 100ms);

    while (true) {
        led1 = !led1;
        printf("Temps de frequence de la led 2 : %d x plus que la led 1.\n", counter);

        ThisThread::sleep_for(BLINKING_RATE);
    }
}
*/


// **********---- TP - I2C Communiquer avec le capteur --------- //
// 1) Récupérer la datasheet du capteur
// --> Datasheet : 
//      https://6tron.io/zest/zest_sensor_p_t_rh_1_0_0
//      https://6tron.io/zest_core/zest_core_fmlr_72_1_0_0 
// 2) Utiliser la documentation (datasheet + site 6TRON) pour trouver comment lire la mesure du capteur
// a. Quelle adresse ? 
//      --> Humidite (0x40), temperature (0x48), pression (0x70)
// b. Quel registre ?
// c. Quelle taille ?
// 3) Récupérer la mesure et l'afficher sur la sortie standard


// **********---- TP - RTOS Ping Pong -------------------------- //
// -> Créer deux fonctions :
//      - ping() : affiche 100x "Ping"
//      - pong() : affiche 100x "Pong"
// -> Créer deux threads qui exécutent les fonctions ping() et pong()
// -> Démarrer les deux threads
// -> Conserver une boucle principale simple :
//      - Clignotement LED
//      - Affichage "Alive!\n"
/*
// Définition de la LED et de la fréquence de clignotement
DigitalOut led(LED1);
const auto BLINKING_RATE = 500ms;

// Fonctions des threads
void ping() {
    for (int i = 0; i < 100; i++) {
        printf("Ping\n");
        ThisThread::sleep_for(10ms); // Pause pour éviter un affichage trop rapide
    }
}

void pong() {
    for (int i = 0; i < 100; i++) {
        printf("Pong\n");
        ThisThread::sleep_for(10ms); // Pause pour éviter un affichage trop rapide
    }
}

int main() {
    printf("Démarrage des threads Ping-Pong...\n");

    // Création des threads
    Thread thread1, thread2;

    // Lancement des fonctions dans les threads
    thread1.start(ping);
    thread2.start(pong);

    // Boucle principale
    while (true) {
        led = !led; // Inverser l'état de la LED pour clignoter
        printf("Alive!\n"); // Afficher un message dans la boucle principale
        ThisThread::sleep_for(BLINKING_RATE);
    }
}
*/
/* COMMENTAIRE */ 
/*
--> Le souci ici, c'est qu'on n'a pas vraiment géré la 
synchronisation et le contrôle de la concurrence entre les 
threads, ce qui peut poser des problèmes quand ils veulent 
accéder aux mêmes ressources.
*/


// **********---- TP - RTOS Ping Pong (suite) ------------------ //
// -> Utiliser les mutex pour finaliser l'exemple de Ping Pong.

/*
// Declaration des threads et ressources partagées
Thread ping_thread;
Thread pong_thread;
Mutex mutex_ping_pong;  // Mutex pour proteger affichage

DigitalOut led(LED1);  // LED pour afficher etat
int ping_count = 0;
int pong_count = 0;

void ping() {
    for (int i = 0; i < 100; i++) {
        mutex_ping_pong.lock();  // Protection de la ressource partagee
        printf("Ping\n");
        ping_count++;
        mutex_ping_pong.unlock();  // Liberation du mutex

        ThisThread::sleep_for(100ms); 
    }
}

void pong() {
    for (int i = 0; i < 100; i++) {
        mutex_ping_pong.lock();  // Protection de la ressource partagee
        printf("Pong\n");
        pong_count++;
        mutex_ping_pong.unlock();  // Liberation du mutex

        ThisThread::sleep_for(100ms);  
    }
}

int main() {
    // Demarrage des threads
    ping_thread.start(ping);
    pong_thread.start(pong);

    while (true) {
        led = !led;  // Clignoter la LED
        printf("Alive!\n");
        ThisThread::sleep_for(500ms);  // Temporisation pour la boucle principale
    }
}
*/
/* COMMENTAIRE */
/*
Pour résoudre le problème de gestion de la concurrence et de la 
synchronisation entre les threads ping() et pong(), nous avons 
utilisé des mutex. Un mutex (mutual exclusion) permet de protéger 
les ressources partagées en s'assurant qu'un seul thread puisse y 
accéder à la fois. Cela évite les conflits entre les threads et 
garantit une exécution plus fluide et sécurisée.
*/

// **********---- TP - RTOS Ping Pong (fin) -------------------- //
// Donner des niveaux de priorités différents aux différents threads pour finaliser l'exemple de Ping Pong.
/*
Pour finaliser l'exemple de RTOS Ping Pong, nous avons attribué des 
priorités différentes aux threads ping() et pong(). En RTOS, la 
priorité d'un thread détermine l'ordre dans lequel il est exécuté. 
Le thread avec la priorité la plus élevée sera exécuté en premier, 
tandis que celui avec la priorité la plus basse attendra son tour.

Nous avons attribué une priorité plus élevée au thread ping(), 
ce qui lui permettait de s'exécuter plus fréquemment. En revanche, 
le thread pong(), avec une priorité plus faible, s'exécutait moins 
souvent. Cette gestion des priorités nous a permis de mieux 
comprendre comment contrôler l'ordre d'exécution des threads et 
comment un thread à haute priorité peut monopoliser l'exécution.
*/