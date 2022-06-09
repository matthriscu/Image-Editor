function out = proximal_2x2(f, STEP = 0.1)
    % ===================================================================================
    % Aplica Interpolare Proximala pe imaginea 2 x 2 f cu puncte intermediare echidistante.
    % f are valori cunoscute în punctele (1, 1), (1, 2), (2, 1) ?i (2, 2).
    % Parametrii:
    % - f = imaginea ce se va interpola;
    % - STEP = distan?a dintre dou? puncte succesive.
    % ===================================================================================
    
    % TODO: Defineste coordonatele x si y ale punctelor intermediare.
    x_int = y_int = 1 : STEP : 2;

    % Se afl? num?rul de puncte.
    n = length(x_int);

    % TODO: Cele 4 puncte încadratoare vor fi aceleasi pentru toate punctele din interior.

    % TODO: Initializeaza rezultatul cu o matrice nula n x n.
    out = zeros(n);

    % Se parcurge fiecare pixel din imaginea finala.
    parfor i = 1 : n
        parfor j = 1 : n
            % TODO: Afla cel mai apropiat pixel din imaginea initiala.
            if x_int(i) < 1.5
              current_x = 1;
            else
              current_x = 2;
            endif
            if y_int(j) < 1.5
              current_y = 1;
            else
              current_y = 2;
            endif
           
            % TODO: Calculeaza pixelul din imaginea finala.
            out(i, j) = f(current_x, current_y);
    
        endparfor
    endparfor

endfunction