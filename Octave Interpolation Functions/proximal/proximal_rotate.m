function R = proximal_rotate(I, rotation_angle)
    % =========================================================================
    % Roteste imaginea alb-negru I de dimensiune m x n cu unghiul rotation_angle,
    % aplicând Interpolare Proximala.
    % rotation_angle este exprimat în radiani.
    % =========================================================================
    [m n nr_colors] = size(I);
    
    % Se converteste imaginea de intrare la alb-negru, daca este cazul.
    if nr_colors > 1
        R = -1;
        return
    endif
    
    I = double(I);

    % Obs:
    % Atunci când se aplica o scalare, punctul (0, 0) al imaginii nu se va deplasa.
    % În Octave, pixelii imaginilor sunt indexati de la 1 la n.
    % Daca se lucreaza în indici de la 1 la n si se inmultesc x si y cu s_x respectiv s_y,
    % atunci originea imaginii se va deplasa de la (1, 1) la (sx, sy)!
    % De aceea, trebuie lucrat cu indici în intervalul [0, n - 1].

    % TODO: Calculeaza cosinus si sinus de rotation_angle.
    c = cos(rotation_angle);
    s = sin(rotation_angle);

    % TODO: Initializeaza matricea finala.
    R = zeros(m, n);

    % TODO: Calculeaza matricea de transformare.
    T = [c, -s; s, c];

    % TODO: Inverseaza matricea de transformare, FOLOSIND doar functii predefinite!
    T_inv = inv(T);

    % Se parcurge fiecare pixel din imagine.
    parfor y = 0 : m - 1
        parfor x = 0 : n - 1
            % TODO: Aplica transformarea inversa asupra (x, y) si calculeaza x_p si y_p
            % din spatiul imaginii initiale.
            
            coords = T_inv * [x; y];

            % TODO: Trece (xp, yp) din sistemul de coordonate [0, n - 1] în
            % sistemul de coordonate [1, n] pentru a aplica interpolarea.
            
            coords += 1;

            % TODO: Daca xp sau yp se afla în exteriorul imaginii,
            % se pune un pixel negru si se trece mai departe.
            if coords(1) < 1 || coords(2) < 1 || coords(1) > n || coords(2) > m
              R(y + 1, x + 1) = 0;
              continue;
            endif

            % TODO: Afla punctele ce înconjoara(xp, yp).
            x1 = floor(coords(1));
            y1 = floor(coords(2));
            x2 = x1 + 1;
            y2 = y1 + 1;
            
            if x2 > n
              x1 = n - 1;
              x2 = n;
            endif
            
            if y2 > m
              y1 = m - 1;
              y2 = m;
            endif

            % TODO: Calculeaza coeficientii de interpolare notati cu a
            % Obs: Se poate folosi o functie auxiliara în care sau se calculeze coeficientii,
            % conform formulei.
            
            a = proximal_coef(I, x1, y1, x2, y2);

            % TODO: Calculeaza valoarea interpolata a pixelului (x, y).
            
            R(y + 1, x + 1) = a(1) + a(2) * coords(1) + a(3) * coords(2) + a(4) * coords(1) * coords(2);
        
        endparfor
    endparfor

    % TODO: Transforma matricea rezultata în uint8 pentru a fi o imagine valida.

    R = cast(R, 'uint8');
    
endfunction
