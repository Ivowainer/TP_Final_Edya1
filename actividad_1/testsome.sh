#!/bin/bash

# Obtén todos los tableros de la carpeta ./tableros
tableros=(./tableros/tablero*.txt)

# Inicializa los contadores
fallados=0
exitosos=0
fallados_archivos=()

# Itera sobre todos los tableros y ejecuta el programa robot
for tablero in "${tableros[@]}"; do
    resultado=$(./robot "$tablero")
    
    # Verifica si el resultado no es ni vacío ni comienza con R, U, D o L
    if [[ -n "$resultado" && ! "$resultado" =~ ^[RUDL] ]]; then
        echo "Error en el tablero: $tablero"
        fallados_archivos+=("$tablero")
        ((fallados++))
    else
        ((exitosos++))
    fi
done

# Imprime los resultados finales
echo "Tableros que fallaron: $fallados"
if [ "$fallados" -gt 0 ]; then
    echo "Archivos fallados:"
    for archivo in "${fallados_archivos[@]}"; do
        echo "$archivo"
    done
fi

echo "Tableros exitosos: $exitosos"
