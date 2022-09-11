function setup () {
  

    var width = 250;
    var height = 200;
    createCanvas (width , height ) ;
    background (0) ;
    for (var x = 0; x < width; x += width / 10) {        
        for (var y = 0; y < height; y += height / 5) {
            stroke (125 , 125 , 125) ;
            strokeWeight (1) ;
            line (x, 0, x, height );
            line (0 , y, width , y);
        }
    }

    var data = [        
        [40 ,70] ,
        [70 ,130] ,
        [90 ,40] ,
        [110 , 100] ,
        [140 ,110] ,
        [160 , 100] ,
        [150 , 30]
        ];
    var point = [140 ,90]; // query    
    for ( let i = 0; i < data.length; i ++) {        
        fill (255 , 255 , 255) ;
        circle (data[i][0], height - data[i][1], 7) ; // 200 -y para q se dibuje apropiadamente
        console.log ( root );
        textSize (8) ;
        (data[i][0]+ ',' + data[i][1], data[i][0]+ 5, height - data[i][1]);// 200 -y para q se dibuje        
    }
    var root = build_kdtree ( data ) ;
    console.log ( root );   
    console.log(closest_point_brute_force(data,point));
    console.log(naive_closest_point(root,point));
    console.log(closest_point(root,point));  
}