import matplotlib.pyplot as plt
import colorsys

def ryb_to_rgb(r, y, b):
    i_w = min(r, y, b)
    r -= i_w
    y -= i_w
    b -= i_w

    max_y = max(r, y, b)

    g = min(y, b)
    y -= g
    b -= g

    if b > 0 and g > 0:
        b *= 2.0
        g *= 2.0

    r += y
    g += y

    max_g = max(r, g, b)

    if max_g > 0:
        n = max_y / max_g
        r *= n
        g *= n
        b *= n

    r += i_w
    g += i_w
    b += i_w

    return (max(0, min(1, r)), max(0, min(1, g)), max(0, min(1, b)))

def rgb_to_hsl(r, g, b):
    """
    Converte uma cor do espaço RGB para HSL.
    Utiliza a biblioteca padrão colorsys.
    """
    h, l, s = colorsys.rgb_to_hls(r, g, b)
    return (h, s, l) 

cores_ryb_primarias = {
    'vermelho': (1.0, 0.0, 0.0),
    'amarelo': (0.0, 1.0, 0.0),
    'azul': (0.0, 0.0, 1.0),
}

def harmonia_complementar_ryb(r, y, b):
    return (1.0 - r, 1.0 - y, 1.0 - b)

if __name__ == '__main__':
    r_ryb, y_ryb, b_ryb = cores_ryb_primarias['vermelho']

    rc_ryb, yc_ryb, bc_ryb = harmonia_complementar_ryb(r_ryb, y_ryb, b_ryb)

    cor_base_rgb = ryb_to_rgb(r_ryb, y_ryb, b_ryb)
    cor_comp_rgb = ryb_to_rgb(rc_ryb, yc_ryb, bc_ryb)

    paleta_ryb_rgb = [cor_base_rgb, cor_comp_rgb]

    print("--- Resultado Corrigido ---")
    print(f"Cor Base RYB: ({r_ryb}, {y_ryb}, {b_ryb}) -> RGB: {cor_base_rgb}")
    print(f"Cor Complementar RYB: ({rc_ryb}, {yc_ryb}, {bc_ryb}) -> RGB: {cor_comp_rgb}")

    plt.imshow([paleta_ryb_rgb])
    plt.title("Harmonia Complementar (RYB -> RGB)")
    plt.axis('off')
