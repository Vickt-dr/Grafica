import colorsys
import re # Importado para validação da entrada

cores_circulo = {
    'vermelho': (1, 0, 0), 'vermelho-laranja': (1, 0.25, 0), 'laranja': (1, 0.5, 0),
    'amarelo-laranja': (1, 0.75, 0), 'amarelo': (1, 1, 0), 'amarelo-verde': (0.5, 1, 0),
    'verde': (0, 1, 0), 'azul-verde': (0, 0.5, 0.5), 'azul': (0, 0, 1),
    'azul-violeta': (0.25, 0, 1), 'violeta': (0.5, 0, 1), 'vermelho-violeta': (1, 0, 0.5)
}
lista_nomes_cores = list(cores_circulo.keys())

def obter_harmonias(nome_cor_base):
    if nome_cor_base not in lista_nomes_cores:
        return None

    idx = lista_nomes_cores.index(nome_cor_base)
    paletas = {}

    paletas['Complementar'] = [lista_nomes_cores[idx], lista_nomes_cores[(idx + 6) % 12]]
    paletas['Análoga'] = [lista_nomes_cores[(idx - 1) % 12], lista_nomes_cores[idx], lista_nomes_cores[(idx + 1) % 12]]
    paletas['Triádica'] = [lista_nomes_cores[idx], lista_nomes_cores[(idx + 4) % 12], lista_nomes_cores[(idx + 8) % 12]]
    paletas['Dividida Complementar'] = [lista_nomes_cores[idx], lista_nomes_cores[((idx + 6) - 1) % 12], lista_nomes_cores[((idx + 6) + 1) % 12]]
    paletas['Tétrade (Retangular)'] = [lista_nomes_cores[idx], lista_nomes_cores[(idx + 2) % 12], lista_nomes_cores[(idx + 6) % 12], lista_nomes_cores[(idx + 8) % 12]]

    return paletas

def hex_para_rgb_normalizado(hex_color):
    hex_color = hex_color.lstrip('#')
    return tuple(int(hex_color[i:i+2], 16) / 255.0 for i in (0, 2, 4))

def mapear_cor_para_circulo(rgb_cor):
    h_cor, _, _ = colorsys.rgb_to_hsv(*rgb_cor)
    menor_distancia = float('inf')
    cor_mais_proxima = None
    for nome, rgb_circulo in cores_circulo.items():
        h_circulo, _, _ = colorsys.rgb_to_hsv(*rgb_circulo)
        distancia = min(abs(h_cor - h_circulo), 1 - abs(h_cor - h_circulo))
        if distancia < menor_distancia:
            menor_distancia = distancia
            cor_mais_proxima = nome
    return cor_mais_proxima

if __name__ == '__main__':

    while True:
        cor_hex_usuario = input("\nDigite o código da cor em formato HEX (ex: #967444): ").strip()
        if re.match(r'^#[0-9a-fA-F]{6}$', cor_hex_usuario):
        else:
            print("Formato inválido. Por favor, use o formato #RRGGBB (ex: #BE3455).")

    cor_rgb_usuario = hex_para_rgb_normalizado(cor_hex_usuario)
    cor_mapeada = mapear_cor_para_circulo(cor_rgb_usuario)

    print(f"\nCor base de referência: {cor_hex_usuario}")
    print(f"Cor mais próxima no círculo cromático: '{cor_mapeada}'")

    paletas_geradas = obter_harmonias(cor_mapeada)

    if paletas_geradas:
        print("\n--- PALETAS HARMÔNICAS GERADAS ---")
        for nome_paleta, cores in paletas_geradas.items():
            cores_str = ", ".join(cores)
            print(f"- Paleta {nome_paleta}: [{cores_str}]")
    else:
        print("Não foi possível gerar as paletas.")