#include <bits/stdc++.h>
using namespace std;

// Macros para simplificar
#define fori(i, n) for (int i = 0; i < (n); i++)
#define fore(i, n) for (int i = 1; i <= (n); i++)
#define pb push_back
#define all(v) v.begin(), v.end()
#define read(a) cin >> a
#define read2(a, b) cin >> a >> b

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;

int n, m, tg;

// Estructura para manejar las piezas más fácilmente
struct Piece {
    int id;
    vector<pair<int, int>> cells;
};

// Función para simular la gravedad en el tablero actual
// Retorna true si el target se movió o algo cambió significativamente, 
// pero aquí lo usamos solo para actualizar el estado del tablero.
void apply_gravity(vvi& current_mat, map<int, vector<pair<int,int>>>& pieces) {
    bool moved = true;
    while (moved) {
        moved = false;
        // Iteramos sobre las piezas. Para evitar problemas de orden, intentamos mover todas.
        // Una optimización sería ordenar por altura, pero con N=50, un while(moved) es suficiente.
        for (auto& [id, cells] : pieces) {
            if (cells.empty()) continue;

            bool can_fall = true;
            for (auto& p : cells) {
                int r = p.first;
                int c = p.second;
                // Si toca el suelo, no puede caer
                if (r + 1 >= n) {
                    can_fall = false;
                    break;
                }
                // Si abajo hay algo que NO es aire (0) y NO es la misma pieza
                int below = current_mat[r + 1][c];
                if (below != 0 && below != id) {
                    can_fall = false;
                    break;
                }
            }

            if (can_fall) {
                moved = true;
                // Borrar posición vieja
                for (auto& p : cells) current_mat[p.first][p.second] = 0;
                // Actualizar coordenadas
                for (auto& p : cells) p.first++;
                // Pintar nueva posición
                for (auto& p : cells) current_mat[p.first][p.second] = id;
            }
        }
    }
}

long long get_cost(string dir, vvi original_mat) {
    si removed;
    long long current_cost = 0;

    while (true) {
        // 1. Reconstruir el estado actual del tablero con las piezas eliminadas
        vvi mat(n, vi(m, 0));
        map<int, vector<pair<int,int>>> pieces;
        
        // Llenamos el tablero solo con las piezas NO eliminadas
        fori(i, n) {
            fori(j, m) {
                int id = original_mat[i][j];
                if (id != 0 && removed.find(id) == removed.end()) {
                    mat[i][j] = id;
                    pieces[id].pb({i, j});
                }
            }
        }

        // 2. APLICAR GRAVEDAD (Las piezas caen si perdieron soporte)
        apply_gravity(mat, pieces);

        // 3. Buscar al Target y verificar si tiene salida libre
        if (pieces.find(tg) == pieces.end()) {
            // El target fue eliminado?? Esto no debería pasar si la lógica es correcta,
            // pero por seguridad retornamos infinito.
            return 1e18; 
        }

        vector<pair<int,int>> tg_cells = pieces[tg];
        si new_blockers;

        for (auto& p : tg_cells) {
            int r = p.first;
            int c = p.second;

            // Lanzar "rayo" en la dirección deseada para ver qué bloquea
            if (dir == "up") {
                for (int k = r - 1; k >= 0; k--) {
                    if (mat[k][c] != 0) new_blockers.insert(mat[k][c]);
                }
            } else if (dir == "down") {
                for (int k = r + 1; k < n; k++) {
                    if (mat[k][c] != 0) new_blockers.insert(mat[k][c]);
                }
            } else if (dir == "left") {
                for (int k = c - 1; k >= 0; k--) {
                    if (mat[r][k] != 0) new_blockers.insert(mat[r][k]);
                }
            } else if (dir == "right") {
                for (int k = c + 1; k < m; k++) {
                    if (mat[r][k] != 0) new_blockers.insert(mat[r][k]);
                }
            }
        }

        // 4. Si no hay nuevos bloqueos, terminamos
        if (new_blockers.empty()) break;

        // 5. Si hay bloqueos, los agregamos a eliminados y REPETIMOS el ciclo
        // (porque al eliminar estos, otras cosas podrían caer y bloquear de nuevo)
        for (int id : new_blockers) {
            if (removed.find(id) == removed.end()) {
                removed.insert(id);
                current_cost += id;
            }
        }
    }
    
    return current_cost;
}

void solve(int caso) {
    read2(n, m);
    vvi mat(n, vi(m));
    fori(i, n) fori(j, m) read(mat[i][j]);
    read(tg);

    long long min_cost = -1;
    string best_pos = "";
    vector<string> dirs = {"left", "right", "up", "down"};

    for (string d : dirs) {
        long long c = get_cost(d, mat); // Pasamos copia de la matriz original
        if (min_cost == -1 || c < min_cost) {
            min_cost = c;
            best_pos = d;
        }
    }
    
    cout << min_cost << " via " << best_pos << "\n";
}

int32_t main() {
    ios::sync_with_stdio(false); cin.tie(0);
    // read(tc); // Descomenta si hay casos
    fore(caso, 1) {
        solve(caso);
    }
}
