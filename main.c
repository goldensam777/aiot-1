#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#define SLEEP_MS(x) Sleep(x)
#else
#include <unistd.h>
#define SLEEP_MS(x) usleep((x)*1000)
#endif

// --- 1. DÉFINITIONS ---
typedef enum {
    STATE_STARTUP,
    STATE_NORMAL,
    STATE_WARNING,
    STATE_ERROR
} SystemState;

// --- 2. VARIABLES GLOBALES ---
SystemState currentState = STATE_STARTUP;
unsigned long globalTick = 0; // Compteur de "ticks" (1 tick = 100ms)

// --- 3. FONCTIONS ---
const char* getStateName(SystemState s) {
    switch(s) {
        case STATE_STARTUP: return "STARTUP";
        case STATE_NORMAL:  return "NORMAL ";
        case STATE_WARNING: return "WARNING";
        case STATE_ERROR:   return "ERROR  ";
        default: return "UNKNOWN";
    }
}

int main() {
    printf("--- SIMULATION IOT DEMARREE ---\n");
    int cycle_de_simulation=100;
    unsigned long int state_error_count=0;
    while (true) {
        // A. LOGIQUE DE TRANSITION (Le Cerveau)
        // TODO: Coder ici le changement d'état automatique (ex: après 100 ticks)
        if (globalTick>0 && globalTick % cycle_de_simulation == 0){
            // Doit suivre le modèle: Commencer avec STARTUP, puis NORMAL -> WARNING -> ERROR -> NORMAL ...
            switch (currentState){
                case STATE_NORMAL:
                    currentState = STATE_WARNING;
                    break;
                case STATE_WARNING:
                    state_error_count=0;
                    currentState = STATE_ERROR;
                    break;
                case STATE_ERROR:
                    currentState = STATE_NORMAL;
                default:
                    break;
            }
        }
        // B. LOGIQUE D'AFFICHAGE (La LED)
        bool ledState = false;

        switch (currentState) {
            case STATE_STARTUP:
                // TODO: Logique de clignotement STARTUP: 3 clignotements rapides, puis passage à NORMAL
                if (globalTick<7)
                    ledState = (globalTick%2);
                else
                    currentState=STATE_NORMAL;
                break;
            case STATE_NORMAL:
                // TODO: Logique de clignotement NORMAL
                // Clignotement lent régulier
                // Astuce: if (globalTick % 10 < 5) ...
                if (globalTick % 10 < 5)
                    ledState=true;
                else
                    ledState=false;
                break;
            case STATE_WARNING:
                // TODO: Logique WARNING
                // Clignotement rapide continu
                if (globalTick%5 == 0)
                    ledState = true;
                else
                    ledState= false;
                break;

            case STATE_ERROR:
                // TODO: Logique ERROR
                // 2 clignotements rapides + pause
                if (state_error_count<4){
                    ledState = (state_error_count%2);
                    state_error_count++;
                }
                else
                    ledState= false;
                break;
        }

        // C. RENDU VISUEL
        // \r permet de revenir au début de la ligne
        printf("\r[ Tps: %5lu ] [ ETAT: %s ]  LED: %s ",
               globalTick,
               getStateName(currentState),
               ledState ? "(O)" : " . ");

        fflush(stdout); // Force l'affichage immédiat

        // D. ATTENTE (CADENCE)
        SLEEP_MS(100); // Pause de 100ms
        globalTick++;
    }

    return 0;
}