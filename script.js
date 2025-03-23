// Function to create a chart
const createChart = (canvasId, data, backgroundColor, borderColor, labels) => {
  return new Chart(document.getElementById(canvasId), {
    type: 'bar',
    data: {
      labels: labels, // Dynamic labels based on dataset
      datasets: [{
        label: 'Clique Size Distribution',
        data: data, // Data for the histogram
        backgroundColor: backgroundColor,
        borderColor: borderColor,
        borderWidth: 1,
        animation: {
          duration: 1000,
          easing: 'easeInOutQuad',
          delay: (context) => context.dataIndex * 200, // Delay between bars
        },
      }],
    },
    options: {
      scales: {
        y: {
          beginAtZero: true,
          grid: {
            color: 'rgba(255, 255, 255, 0.1)',
          },
          title: {
            display: true,
            text: 'Number of Cliques',
          },
        },
        x: {
          grid: {
            color: 'rgba(255, 255, 255, 0.1)',
          },
          title: {
            display: true,
            text: 'Clique Size',
          },
        },
      },
      plugins: {
        legend: {
          labels: {
            font: {
              size: 14,
              weight: 'bold',
            },
          },
        },
      },
    },
  });
};

// Data for Wiki-Vote dataset
const wikiVoteData = [8655, 13718, 27292, 48416, 68872, 83266, 76732, 54456, 35470, 21736, 11640, 5449, 2329, 740, 208, 23];
const wikiVoteLabels = ['Size 2', 'Size 3', 'Size 4', 'Size 5', 'Size 6', 'Size 7', 'Size 8', 'Size 9', 'Size 10', 'Size 11', 'Size 12', 'Size 13', 'Size 14', 'Size 15', 'Size 16', 'Size 17'];

// Data for Email-Enron dataset
const emailEnronData = [14070, 7077, 13319, 18143, 22715, 25896, 24766, 22884, 21393, 17833, 15181, 11487, 7417, 3157, 1178, 286, 41, 10, 6];
const emailEnronLabels = ['Size 2', 'Size 3', 'Size 4', 'Size 5', 'Size 6', 'Size 7', 'Size 8', 'Size 9', 'Size 10', 'Size 11', 'Size 12', 'Size 13', 'Size 14', 'Size 15', 'Size 16', 'Size 17', 'Size 18', 'Size 19', 'Size 20'];

// Data for AS-Skitter dataset
const asSkitterData = [
  2319807, 3171609, 1823321, 939336, 684873, 598284, 588889, 608937, 665661, 728098, 798073, 877282, 945194, 980831, 939987, 839330, 729601, 639413, 600192, 611976, 640890, 673924, 706753, 753633, 818353, 892719, 955212, 999860, 1034106, 1055653, 1017560, 946717, 878552, 809485, 744634, 663650, 583922, 520239, 474301, 420796, 367879, 321829, 275995, 222461, 158352, 99522, 62437, 39822, 30011, 25637, 17707, 9514, 3737, 2042, 1080, 546, 449, 447, 405, 283, 242, 146, 84, 49, 22, 4
];
const asSkitterLabels = Array.from({ length: 66 }, (_, i) => `Size ${i + 2}`); // Generates labels from Size 2 to Size 67

// Initialize Charts for Each Page
if (document.getElementById('histogram1')) {
  // Wiki-Vote Dataset
  createChart('histogram1', wikiVoteData, 'rgba(75, 192, 192, 0.2)', 'rgba(75, 192, 192, 1)', wikiVoteLabels);

  // Email-Enron Dataset
  createChart('histogram2', emailEnronData, 'rgba(153, 102, 255, 0.2)', 'rgba(153, 102, 255, 1)', emailEnronLabels);

  // AS-Skitter Dataset
  createChart('histogram3', asSkitterData, 'rgba(255, 159, 64, 0.2)', 'rgba(255, 159, 64, 1)', asSkitterLabels);
}