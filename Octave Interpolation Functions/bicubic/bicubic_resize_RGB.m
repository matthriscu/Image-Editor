function out = bicubic_resize_RGB(img, p, q)
    % =========================================================================
    % Redimensioneaza imaginea img astfel �nc�t aceasta save fie de dimensiune p x q.
    % Imaginea img este colorata.
    % =========================================================================

    % TODO: Extrage canalul rosu al imaginii.
    R = img(:, :, 1);
    
    % TODO: Extrage canalul verde al imaginii.
    G = img(:, :, 2);
    
    % TODO: Extrage canalul albastru al imaginii.
    B = img(:, :, 3);
    
    % TODO: Aplica functia bicubic pe cele 3 canale ale imaginii.    
    % TODO: Formeaza imaginea finala concatenand cele 3 canale de culori.
    
    out(:, :, 1) = bicubic_resize(R, p, q);
    out(:, :, 2) = bicubic_resize(G, p, q);
    out(:, :, 3) = bicubic_resize(B, p, q);

endfunction
