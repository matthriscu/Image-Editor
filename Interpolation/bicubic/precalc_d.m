function [Ix, Iy, Ixy] = precalc_d(I)
    % =========================================================================
    % Prealculeaza matricile Ix, Iy si Ixy ce contin derivatele dx, dy, dxy ale 
    % imaginii I pentru fiecare pixel al acesteia.
    % =========================================================================
    
    % Obtinem dimensiunea imaginii.
    [m n nr_colors] = size(I);
    
    % TODO: Tranforma matricea I in double.
    I = double(I);

    % TODO: Calculeaza matricea cu derivate fata de x Ix.
    Ix = zeros(m, n);
    parfor y = 1 : m
      parfor x = 2 : n - 1
        Ix(y, x) = fx(I, x, y);
      endparfor
    endparfor

    % TODO: Calculeaza matricea cu derivate fata de y Iy.
    Iy = zeros(m, n);
    parfor y = 2 : m - 1
      parfor x = 1 : n
        Iy(y, x) = fy(I, x, y);
      endparfor
    endparfor

    % TODO: Calculeaza matricea cu derivate fata de xy Ixy.
    Ixy = zeros(m, n);
    parfor y = 2 : m - 1
      parfor x = 2 : n - 1
        Ixy(y, x) = fxy(I, x, y);
      endparfor
    endparfor

endfunction
