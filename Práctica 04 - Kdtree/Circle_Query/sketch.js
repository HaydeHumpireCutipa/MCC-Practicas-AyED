let root = null;
function setup() {
  var width = 800;
  var height = 300;
  var factor = 7;
  createCanvas(width, height);

  max_altura = weight_height.data[0][1];
  max_peso = weight_height.data[0][0];
  min_altura = weight_height.data[0][1];
  min_peso = weight_height.data[0][0];

  for (let i = 1; i < weight_height.data.length; i++) {
    if (weight_height.data[i][1] > max_altura) {
      max_altura = weight_height.data[i][1];
    }
    if (weight_height.data[i][1] < min_altura) {
      min_altura = weight_height.data[i][1];
    }

    if (weight_height.data[i][0] > max_peso) {
      max_peso = weight_height.data[i][0];
    }

    if (weight_height.data[i][0] < min_peso) {
      min_peso = weight_height.data[i][0];
    }
  }
  background(0);
  for (var x = 0; x < width; x += width / 10) {
    for (var y = 0; y < height; y += height / 5) {
      stroke(125, 125, 125);
      strokeWeight(1);
      line(x, 0, x, height);
      line(0, y, width, y);
    }
  }
  var data = [];
  // for (let i = 0; i < 250; i++) {
  //   var x = Math.floor(Math.random() * width);
  //   var y = Math.floor(Math.random() * height);
  //   data.push([x, y]);
  //   fill(255, 255, 255);
  //   circle(x, height - y, 7); //200-y para q se dibuje apropiadamente
  //   textSize(11);
  //   text(x + ',' + y, x + 5, height - y); //200-y para q se dibuje apropiadamente
  // }
  for (let i = 0; i < weight_height.data.length; i++) {
    var x = (weight_height.data[i][0] - min_peso) * (factor * 0.5) + 20;
    var y = (weight_height.data[i][1] - min_altura) * factor;
    var gender = weight_height.labels[i];
    data.push([x, y]);
    if (gender == 'Mujer') {
      fill(255, 105, 180);
    } else {
      fill(0, 0, 255);
    }
    circle(x, height - y, 7); //200-y para q se dibuje apropiadamente
    // textSize(11);
    // text(x + ',' + y, x + 5, height - y); //200-y para q se dibuje apropiadamente
  }
  noFill();
  let x_test_c = Math.floor(Math.random() * height);
  let y_test_c = Math.floor(Math.random() * height);
  let x_test_r = Math.floor(Math.random() * height);
  let y_test_r = Math.floor(Math.random() * height);
  var queue = [];

  root = build_kdtree(data);
  console.log(root);
  myDiagram.model = model;
  console.log('Altura del Arbol es ' + getHeight(root));
  // console.log(generate_dot(root));
  // graph
  stroke(0, 255, 0);
  circle(x_test_c, height - y_test_c, 100);
  strokeWeight(1);
  const c_points = range_query_circle(root, [x_test_c, y_test_c], 50, queue);
  console.log({ points: c_points, circle: [x_test_c, y_test_c], radious: 50 });
  //painting green
  for (let i in c_points) {
    strokeWeight(7);
    let [dist, x, y] = c_points[i];
    point(x, height - y);
  }
  //graph rectangle
  let range = {
    center: [x_test_r, y_test_r],
    w: (Math.random() + 1) * 50,
    h: (Math.random() + 1) * 50,
  };
  stroke(255, 255, 0);
  strokeWeight(7);
  point(range.center[0], height - range.center[1]);
  point(x_test_c, height - y_test_c);
  stroke(255, 0, 0);
  strokeWeight(1);
  /*
  rect(
    range.center[0] - range.w,
    height - range.center[1] - range.h,
    range.w * 2,
    range.h * 2
  );
  const r_points = [];
  range_query_rec(root, range, r_points);
  console.log({ points: r_points, range: range });
  //painting red
  for (let i in r_points) {
    strokeWeight(7);
    let [x, y] = r_points[i];
    point(x, height - y);
  }*/

  model.nodeDataArray = gg(root);
}
