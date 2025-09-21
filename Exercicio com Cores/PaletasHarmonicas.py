import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import colorsys

cores_circulo_corrigido = {
    'vermelho': (1, 0, 0),
    'vermelho-laranja': (1, 0.25, 0),
    'laranja': (1, 0.5, 0),
    'amarelo-laranja': (1, 0.75, 0),
    'amarelo': (1, 1, 0),
    'amarelo-verde': (0.5, 1, 0),
    'verde': (0, 1, 0),
    'azul-verde': (0, 0.5, 0.5), 
    'azul': (0, 0, 1),
    'azul-violeta': (0.25, 0, 1), 
    'violeta': (0.5, 0, 1),
    'vermelho-violeta': (1, 0, 0.5) 
}

lista_nomes_cores_corrigida = list(cores_circulo_corrigido.keys())

def obter_harmonias_corrigido(nome_cor_base):
    if nome_cor_base not in lista_nomes_cores_corrigida:
        return None

    idx = lista_nomes_cores_corrigida.index(nome_cor_base)
    paletas = {}

    comp_idx = (idx + 6) % 12
    paletas['Complementar'] = [lista_nomes_cores_corrigida[idx], lista_nomes_cores_corrigida[comp_idx]]

    ana1_idx = (idx - 1) % 12
    ana2_idx = (idx + 1) % 12
    paletas['Análoga'] = [lista_nomes_cores_corrigida[ana1_idx], lista_nomes_cores_corrigida[idx], lista_nomes_cores_corrigida[ana2_idx]]

    tri1_idx = (idx + 4) % 12
    tri2_idx = (idx + 8) % 12
    paletas['Triádica'] = [lista_nomes_cores_corrigida[idx], lista_nomes_cores_corrigida[tri1_idx], lista_nomes_cores_corrigida[tri2_idx]]

    div1_idx = (comp_idx - 1) % 12
    div2_idx = (comp_idx + 1) % 12
    paletas['Dividida Complementar'] = [lista_nomes_cores_corrigida[idx], lista_nomes_cores_corrigida[div1_idx], lista_nomes_cores_corrigida[div2_idx]]

    tet1_idx = (idx + 2) % 12
    tet2_idx = (idx + 6) % 12
    tet3_idx = (idx + 8) % 12
    paletas['Tétrade'] = [lista_nomes_cores_corrigida[idx], lista_nomes_cores_corrigida[tet1_idx], lista_nomes_cores_corrigida[tet2_idx], lista_nomes_cores_corrigida[tet3_idx]]

    cor_rgb = cores_circulo_corrigido[nome_cor_base]
    h, l, s = colorsys.rgb_to_hls(*cor_rgb)
    paleta_mono = []
    for i in range(4):
        novo_l = min(1, l + (i * 0.15))
        novo_s = max(0, s - (i * 0.1))
        paleta_mono.append(colorsys.hls_to_rgb(h, novo_l, novo_s))
    paletas['Monocromática'] = paleta_mono

    return paletas

def visualizar_paletas(paletas, cores_dict):
    num_paletas = len(paletas)
    fig, axs = plt.subplots(num_paletas, 1, figsize=(6, num_paletas * 1.5))
    fig.suptitle("Paletas Harmônicas Geradas (Versão Corrigida)", fontsize=16)

    for i, (titulo, nomes_ou_valores) in enumerate(paletas.items()):
        if titulo == 'Monocromática':
            cores_rgb = nomes_ou_valores
        else:
            cores_rgb = [cores_dict[nome] for nome in nomes_ou_valores]
        
        axs[i].imshow([cores_rgb], aspect='auto')
        axs[i].set_title(titulo)
        axs[i].axis('off')

    plt.tight_layout(rect=[0, 0, 1, 0.96])
    plt.savefig("paletas_harmonicas.png") 
    print("\nVisualização das paletas salva como 'paletas_harmonicas.png'")

if __name__ == '__main__':
    cor_input = input(f"Digite uma cor do círculo cromático ({', '.join(lista_nomes_cores_corrigida)}): ").lower()

    paletas_geradas = obter_harmonias_corrigido(cor_input)

    if paletas_geradas:
        print(f"\nPaletas harmônicas para a cor: {cor_input}\n")
        for nome_paleta, cores in paletas_geradas.items():
            if nome_paleta != 'Monocromática':
                 print(f"Paleta {nome_paleta}: {cores}")
        
        visualizar_paletas(paletas_geradas, cores_circulo_corrigido)
    else:
        print("Cor não encontrada no círculo cromático.")