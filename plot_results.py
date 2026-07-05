import matplotlib.pyplot as plt

print("--- Generating Performance Comparison Graph ---")

# Data gathered from your Day 2 baseline and Day 3 optimized runs
categories = ['Fixed-Timer Baseline', 'Python Dynamic Optimizer']
delay_scores = [9, 4]  # 9 seconds from your fixed baseline, approx 4 from optimized

# Create a clean bar chart
plt.figure(figsize=(8, 5))
colors = ['#ff4d4d', '#2ec4b6']  # Red for baseline, Teal for optimizer

plt.bar(categories, delay_scores, color=colors, width=0.4, edgecolor='black', linewidth=1.2)

# Styling the graph for a professional look
plt.title('Traffic Signal Optimization: Total Vehicle Delay Comparison', fontsize=14, fontweight='bold', pad=15)
plt.xlabel('Control Strategy System', fontsize=12, fontweight='bold', labelpad=10)
plt.ylabel('Total Cumulative Delay (vehicle-seconds)', fontsize=12, fontweight='bold', labelpad=10)
plt.grid(axis='y', linestyle='--', alpha=0.7)

# Add value labels on top of the bars
for i, v in enumerate(delay_scores):
    plt.text(i, v + 0.3, f"{v}s", ha='center', fontweight='bold', fontsize=11)

# Save the graph as an image inside your project folder
plt.tight_layout()
plt.savefig('traffic_performance_chart.png', dpi=300)
print(">> Success! 'traffic_performance_chart.png' has been saved to your project folder.")