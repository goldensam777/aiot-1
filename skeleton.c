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

    while (true) {
        // A. LOGIQUE DE TRANSITION (Le Cerveau)
        // TODO: Coder ici le changement d'état automatique (ex: après 100 ticks)

        // B. LOGIQUE D'AFFICHAGE (La LED)
        bool ledState = false;

        switch (currentState) {
            case STATE_STARTUP:
                // TODO: Logique de clignotement STARTUP
                break;
            case STATE_NORMAL:
                // TODO: Logique de clignotement NORMAL
                // Astuce: if (globalTick % 10 < 5) ...
                break;
            case STATE_WARNING:
                // TODO: Logique WARNING
                break;
            case STATE_ERROR:
                // TODO: Logique ERROR
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