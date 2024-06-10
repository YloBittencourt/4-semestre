import numpy as np
import matplotlib.pyplot as plt

# Gerar dados
np.random.seed(0)
x = np.random.normal(loc=10, scale=2, size=int(1e3))

# Calcular os quartis
q = np.percentile(x, [25, 50, 75])

# Amplitude interquartil (IQR)
iqr = q[2] - q[0]

# Limites para outliers
out_low = q[0] - 1.5 * iqr
out_upp = q[2] + 1.5 * iqr

# Min e Max não outliers
min_no = x[x >= out_low].min()
max_no = x[x <= out_upp].max()

# Configuração do layout dos gráficos
fig, axes = plt.subplots(1, 2, gridspec_kw={'width_ratios': [3, 1]}, figsize=(12, 8))
box_ax, hist_ax = axes

# Configurações do boxplot
box_ax.set_ylim([min(x) - 0.2 * iqr, max(x) + 0.2 * iqr])
boxprops = dict(facecolor='lightgrey')
box_ax.boxplot(x, vert=True, patch_artist=True, boxprops=boxprops)
box_ax.set_xticks([])
box_ax.set_yticks(np.round([min(x), q[0], q[1], q[2], max(x)], 1))
box_ax.set_yticklabels(np.round([min(x), q[0], q[1], q[2], max(x)], 1))

# Textos dos quartis
for i in range(3):
    box_ax.text(1.1, q[i], f'q{i+1}', va='center')

# Deslocamento para os textos
offset = 0.3

# Textos do mínimo e máximo não outliers
box_ax.text(1.1, min_no + offset, 'Min. no outlier', color='blue', va='bottom')
box_ax.text(1.1, max_no - offset, 'Max. no outlier', color='blue', va='top')

# Textos dos valores de mínimo e máximo não outliers
box_ax.text(1.3, min_no - offset, f'({round(min_no, 1)})', color='blue', va='top')
box_ax.text(1.3, max_no + offset, f'({round(max_no, 1)})', color='blue', va='bottom')

# Segmentos de IQR
box_ax.plot([1.3, 1.4], [q[0], q[0]], 'r--')
box_ax.plot([1.3, 1.4], [q[2], q[2]], 'r--')
box_ax.plot([1.35, 1.35], [q[0], q[0] + 0.3 * iqr], 'r--')
box_ax.plot([1.35, 1.35], [q[2], q[2] - 0.3 * iqr], 'r--')
box_ax.text(1.35, q[1], 'iqr = q3 - q1', color='red')

# Limites superiores e inferiores
box_ax.plot([1.3, 1.4], [out_upp, out_upp], 'r--')
box_ax.plot([1.3, 1.4], [out_low, out_low], 'r--')
box_ax.plot([1.35, 1.35], [q[2], out_upp], 'r--')
box_ax.plot([1.35, 1.35], [q[0], out_low], 'r--')

# Texto dos limites
box_ax.text(1.3, out_low, 'q1 - 1.5iqr', color='red', va='top')
box_ax.text(1.3, out_upp, 'q3 + 1.5iqr', color='red', va='bottom')
box_ax.text(1.18, out_low, f'({round(out_low, 1)})', color='red', va='top')
box_ax.text(1.18, out_upp, f'({round(out_upp, 1)})', color='red', va='bottom')

# Setas para outliers
if min(x) < min_no:
    box_ax.arrow(1.5, out_low, 0, min(x) - out_low, head_width=0.05, head_length=0.2, fc='red', ec='red')
    #box_ax.text(1.35, out_low, 'Outlier', color='red', va='top')

if max(x) > max_no:
    box_ax.arrow(1.5, out_upp, 0, max(x) - out_upp, head_width=0.05, head_length=0.2, fc='red', ec='red')
    #box_ax.text(1.35, out_upp, 'Outlier', color='red', va='bottom')

# Segmentos percentuais
box_ax.plot([0.65, 0.65], [min(x), max(x)], 'g-')
box_ax.scatter([0.65] * 5, [min(x), q[0], q[1], q[2], max(x)], color='darkgreen')
for perc, label in zip([min(x), q[0], q[1], q[2], max(x)], ['25%', '25%', '25%', '25%']):
    box_ax.text(0.55, perc + (q[1] - perc) / 2 if perc != max(x) else perc - (perc - q[2]) / 2, label, color='darkgreen')

# Histograma
hist_ax.hist(x, bins=50, orientation='horizontal', color='lightgrey', edgecolor='white')
hist_ax.axhline(y=out_low, color='red', linestyle='--')
hist_ax.axhline(y=q[0], color='red', linestyle='--')
hist_ax.axhline(y=q[1], color='red', linestyle='--')
hist_ax.axhline(y=q[2], color='red', linestyle='--')
hist_ax.axhline(y=out_upp, color='red', linestyle='--')

hist_ax.set_xlim([0, hist_ax.get_xlim()[1]])
hist_ax.set_ylim([min(x) - 0.2 * iqr, max(x) + 0.2 * iqr])
hist_ax.set_yticks([])

plt.tight_layout()
plt.show()
