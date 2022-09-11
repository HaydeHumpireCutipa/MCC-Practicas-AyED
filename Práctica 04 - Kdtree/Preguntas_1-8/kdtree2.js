k = 2;
class Node {
  constructor(point, axis) {
    this.point = point;
    this.left = null;
    this.right = null;
    this.axis = axis;
  }
}

function getHeight(node) {
  if (node == null) return 0;
  var Hleft = getHeight(node.left) + 1;
  var Hright = getHeight(node.right) + 1;

  if (Hleft > Hright) return Hleft;
  return Hright;
}

function generate_dot(node) {
  if (!node) return;
  var left = node.left;
  var right = node.right;
  if (left) {
    console.log('"' + node.point + '"' + '->' + '"' + left.point + '"');
    generate_dot(left);
  }
  if (right) {
    console.log('"' + node.point + '"' + '->' + '"' + right.point + '"');
    generate_dot(right);
  }
}

function build_kdtree(points, depth = 0) {
  if (points.length == 0) return;

  var axis = depth % k;
  points.sort((a, b) => (a[axis] > b[axis] ? 1 : b[axis] > a[axis] ? -1 : 0));

  var median = Math.floor(points.length / 2);

  var node = new Node(points[median], axis);
  node.left = build_kdtree(points.slice(0, median), depth + 1);
  node.right = build_kdtree(points.slice(median + 1, points.length), depth + 1);

  return node;
}

const closest_point_brute_force = (points, point) => {
  let pair = [Infinity, null];
  for (let i = 0; i < points.length; i++) {
    let currDist = $distance(points[i], point);
    pair = pair[0] > currDist ? [currDist, points[i]] : pair;
  }
  return pair;
};

const naive_closest_point = (node, point, depth = 0, best = null) => {
  if (!node) return best;
  if (!best) best = [Infinity, null];
  let dist_node = $distance(node.point, point);
  if (best[0] > dist_node) best = [dist_node, node.point];
  let axis = depth % k;
  if (JSON.stringify(node.point) === JSON.stringify(point)) return best;
  else if (node.point[axis] > point[axis])
    return naive_closest_point(node.left, point, depth + 1, best);
  else if (node.point[axis] < point[axis])
    return naive_closest_point(node.right, point, depth + 1, best);
};

const $distance = (a, p) => {
    //euclidean distance
    if (a.length != p.length) return null;
    let dist = 0;
    for (let i = 0; i < a.length; i++) {
      dist += (a[i] - p[i]) ** 2;
    }
    return Math.sqrt(dist);
  };

const closest_point = (node, point, depth = 0, best = null) => {
   if (!node) return best;
   if (!best) best = [Infinity, null];
   let dist_node = $distance(node.point, point);

   if (best[0] > dist_node) best = [dist_node, node.point];
   let axis = depth % k;
   if (node.point[axis] > point[axis]) {
     let closest_pair = closest_point(node.left, point, depth + 1, best);
     console.log({ Lpair: closest_pair });
     console.log({ Ldist: dist_node });
     return closest_pair[0] > dist_node
       ? closest_point(node.right, point, depth + 1, best)
       : closest_pair;
   } else if (node.point[axis] < point[axis]) {
     let closest_pair = closest_point(node.right, point, depth + 1, best);
     console.log({ Rpair: closest_pair });
     console.log({ Rdist: dist_node });
     return closest_pair[0] > dist_node
       ? closest_point(node.left, point, depth + 1, best)
       : closest_pair;
   } else if (JSON.stringify(node.point) === JSON.stringify(point)) {
     return [point, 0];
   }
};