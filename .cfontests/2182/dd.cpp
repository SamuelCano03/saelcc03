#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

const int INF = 1e9;

int K_target, N;
int start_x, start_y;
int x_min, y_min, x_max, y_max;

// Memoización: [ball_x][dir_idx][bounces][paddle_x]
// dir_idx: 0 (izq), 1 (der) cuando la bola baja
int memo[30][2][25][30];

// Verifica si el paddle entero cabe en la pantalla
bool is_paddle_valid(int px) {
    return (px - N / 2) >= x_min && (px + N / 2) <= x_max;
}

// Simula la caída libre de la bola para ver si conseguimos los rebotes faltantes
// Retorna true si logramos llegar a K rebotes antes de tocar el suelo
bool check_drop_win(int bx, int by, int bdx, int bdy, int current_bounces) {
    // Copia local para simular
    int cx = bx, cy = by;
    int cdx = bdx, cdy = bdy;
    int cb = current_bounces;

    while (true) {
        if (cb >= K_target) return true; // Ganamos durante la caída
        if (cy <= y_min) return false;   // Tocó suelo sin llegar a K

        // Mover bola
        cx += cdx;
        cy += cdy;

        // Rebotes laterales durante la caída (bajo el nivel del paddle)
        if (cx <= x_min) {
            cx = x_min; cdx = 1; cb++;
        } else if (cx >= x_max) {
            cx = x_max; cdx = -1; cb++;
        }
        
        // Nota: No chequeamos rebote superior porque estamos cayendo hacia la muerte
    }
}

int solve(int bx, int by, int bdx, int bdy, int bounces, int px) {
    // --- FASE 1: SIMULACIÓN DE FÍSICA (Avanzar hasta evento) ---
    
    // Bucle para avanzar la bola hasta que toque el paddle, gane o pierda
    while (true) {
        // 1. Chequeo de Victoria
        if (bounces >= K_target) return 0;
        
        // 2. Chequeo de Derrota (Suelo)
        if (by <= y_min) return INF;

        // 3. Evento Crítico: Bola al nivel del paddle y bajando
        if (by == start_y && bdy == -1) {
            break; // Salimos del while para tomar decisiones
        }

        // Movimiento Físico Normal
        bx += bdx;
        by += bdy;

        // Rebotes en Paredes
        if (bx <= x_min) {
            bx = x_min; bdx = 1; bounces++;
        } else if (bx >= x_max) {
            bx = x_max; bdx = -1; bounces++;
        }
        
        // Rebote en Techo
        if (by >= y_max) {
            by = y_max; bdy = -1; bounces++;
        }
    }

    // --- FASE 2: TOMA DE DECISIONES (Recursión) ---
    
    // Memoización
    int dir_idx = (bdx == -1) ? 0 : 1;
    // Ajustamos índices para evitar negativos si x_min es > 0 (aunque el input suele normalizarse)
    // Asumiendo coordenadas absolutas 0-25.
    if (memo[bx][dir_idx][bounces][px] != -1) return memo[bx][dir_idx][bounces][px];

    int best_max_dist = INF;

    // --- OPCIÓN A: DEJARLA CAER (DROP) ---
    // Si al dejarla pasar, rebota en paredes y llega a K antes del suelo, el costo es 0.
    if (check_drop_win(bx, by, bdx, bdy, bounces)) {
        // Si podemos ganar dejando caer, el costo es 0.
        best_max_dist = 0;
        return memo[bx][dir_idx][bounces][px] = 0; 
    }

    // --- OPCIÓN B: ATRAPAR CON BORDE IZQUIERDO ---
    // Bola golpea (nuevo_px - N/2) -> nuevo_px = bx + N/2
    int npx_L = bx + N / 2;
    if (is_paddle_valid(npx_L)) {
        int cost = abs(npx_L - px);
        // Rebote especial: Sale hacia arriba-izquierda (dx=-1, dy=1)
        // Importante: Pasamos dy=1 para que en la sig llamada la física avance
        int res = solve(bx, by, -1, 1, bounces + 1, npx_L); 
        if (res != INF) {
            best_max_dist = min(best_max_dist, max(cost, res));
        }
    }

    // --- OPCIÓN C: ATRAPAR CON BORDE DERECHO ---
    // Bola golpea (nuevo_px + N/2) -> nuevo_px = bx - N/2
    int npx_R = bx - N / 2;
    if (is_paddle_valid(npx_R)) {
        int cost = abs(npx_R - px);
        // Rebote especial: Sale hacia arriba-derecha (dx=1, dy=1)
        int res = solve(bx, by, 1, 1, bounces + 1, npx_R);
        if (res != INF) {
            best_max_dist = min(best_max_dist, max(cost, res));
        }
    }

    // --- OPCIÓN D: ATRAPAR CON CENTRO ---
    // El centro del paddle debe estar tal que: npx - N/2 < bx < npx + N/2
    // Rango de npx válidos: (bx - N/2) < npx < (bx + N/2)
    int min_valid_px = bx - N / 2 + 1;
    int max_valid_px = bx + N / 2 - 1;

    for (int npx = min_valid_px; npx <= max_valid_px; npx++) {
        if (is_paddle_valid(npx)) {
            int cost = abs(npx - px);
            // Rebote normal: Mantiene dx, dy se invierte a 1
            int res = solve(bx, by, bdx, 1, bounces + 1, npx);
            if (res != INF) {
                best_max_dist = min(best_max_dist, max(cost, res));
            }
        }
    }

    return memo[bx][dir_idx][bounces][px] = best_max_dist;
}

int main() {
    // Optimización I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (cin >> K_target) {
        cin >> start_x >> start_y;
        cin >> N;
        cin >> x_min >> y_min >> x_max >> y_max;

        memset(memo, -1, sizeof(memo));

        // Inicio: La bola se lanza desde el paddle hacia arriba-izquierda (dx=-1, dy=1)
        // Como la función solve comienza simulando hasta que dy=-1, 
        // podemos llamarla directamente con el estado inicial.
        // La bola subirá, rebotará paredes/techo y eventualmente bajará.
        int ans = solve(start_x, start_y, -1, 1, 0, start_x);

        cout << ans << endl;
    }
    return 0;
}
