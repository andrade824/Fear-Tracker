import QtQuick 2.4
import DataStorage 1.0

Canvas {
    id: canvas
    antialiasing: true
    smooth: true
    renderTarget: Canvas.FramebufferObject
    renderStrategy: Canvas.Cooperative

    // Padding properties
    property int paddingX: 50   // How much padding from the left of the canvas to draw the y-axis
    property int paddingY: 30   // How much padding from the bottom of the canvas to draw the x-axis
    property int labelPaddingX: 15 // How much padding between the label and the x-axis
    property int labelPaddingY: 20 // How much padding between the label and the y-axis

    // Graph range properties
    property int minX: 0    // The smallest X value to be displayed
    property int maxX: 10   // The largest X value to be displayed
    property int rangeX: maxX - minX    // The range of x values being displayed
    property int unitIncrementX: 1000   // A label will be placed every unitIncrementX above the minX

    property int minY: 0    // The smallest Y value to be displayed
    property int maxY: 10   // The largest Y value to be displayed
    property int rangeY: maxY - minY    // The range of Y values being displayed
    property int unitIncrementY: 10   // A label will be placed every unitIncrementY above the minY

    // Data properties
    property var data   // Cache of the data being displayed
    property int type: FearDataNode.TYPE_HEART   // What data to actual output (heartrate, sweat, etc.)

    // Misc properties
    property int availableWidth: width - paddingX   // The actual width of the graph that's getting drawn
    property int availableHeight: height - paddingY;    // The actual height of the graph that's getting drawn
    property real xUnitPerPix: rangeX / availableWidth // How many X units each pixel represents
    property real yUnitPerPix: rangeY / availableHeight // How many Y units each pixel represents
    property int yTickMarkHalfWidth: 8 // How wide each tick mark in the Y-axis should be
    property int secondaryLineWidth: 2  // Width of axis and label lines

    Timer {
         interval: 500;
         running: true;
         repeat: true
         onTriggered: {
             canvas.data = TestData.getLatestData(canvas.type, 75);
             canvas.requestPaint();
         }
     }

    onPaint: {
        console.time("wholeFunction");

        var ctx = canvas.getContext("2d");
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        // Generate test data
        /*for(var i = 0; i < 400; i++) {
            console.log('{ X: "' + i * 1258 + '", Y: ' + Math.floor((Math.random() * 100) + 1) + ' },');
        }*/

        // Default paint settings
        ctx.lineWidth = canvas.secondaryLineWidth;
        ctx.strokeStyle = "#333";
        ctx.font = "8pt sans-serif";
        ctx.textAlign = "center";
        ctx.fillStyle = "#aaa";

        // Set minimum and maximum X and Y values
        canvas.minX = data[0];
        canvas.maxX = data[data.length - 2];

        // Draw Axes
        ctx.beginPath();
        ctx.moveTo(paddingX, 0);
        ctx.lineTo(paddingX, height - paddingY);
        ctx.lineTo(width, height - paddingY);
        ctx.stroke();

        /* Draw X-axis text */
        ctx.strokeStyle = "#aaa";
        var labelXHeight = availableHeight + labelPaddingX;
        var xcoord;
        for(var labelX = minX + unitIncrementX; labelX <= maxX; labelX += unitIncrementX) {
            xcoord = getXPixel(labelX) + paddingX;
            ctx.fillText(milliToTime(labelX), xcoord, labelXHeight);
            ctx.moveTo(xcoord, availableHeight);
            ctx.lineTo(xcoord, 0);
        }

        ctx.stroke();

        // Draw Y-axis text
        var labelXCoord = paddingX - labelPaddingY;
        var ycoord;
        ctx.textBaseline = "middle";
        for(var labelY = minY + unitIncrementY; labelY <= maxY; labelY += unitIncrementY) {
            ycoord = availableHeight - getYPixel(labelY);
            ctx.fillText(labelY, labelXCoord, ycoord);
            ctx.moveTo(paddingX - yTickMarkHalfWidth, ycoord);
            ctx.lineTo(paddingX + yTickMarkHalfWidth, ycoord);
        }

        ctx.stroke();

        // Draw Graph
        ctx.strokeStyle = "#f00"
        ctx.beginPath();
        ctx.moveTo(getXPixel(data[0]) + paddingX + secondaryLineWidth, availableHeight - getYPixel(data[1]) - secondaryLineWidth);

        console.time("drawLines");
        for(var i = 2; i < data.length; i += 2)
            ctx.lineTo(getXPixel(data[i]) + paddingX + secondaryLineWidth, availableHeight - getYPixel(data[i + 1]) - secondaryLineWidth);
        console.timeEnd("drawLines");

        ctx.stroke();
        console.timeEnd("wholeFunction");
    }

    function getMaxY(data) {
        var max = 0;

        for(var i = 0; i < data.length; i++) {
            if(data[i].Y > max) {
                max = data[i].Y;
            }
        }

        max += 10 - max % 10;
        return max;
    }

    /**
    *   @brief  Gives the x-coordinate that the given value should be placed at
    *
    *   @param  xval    The x-value to determine the x-coordinate of
    *
    *   @return The x-coordinate that the given x-value should be drawn at
    */
    function getXPixel(xval) {
        return Math.round((xval - canvas.minX) / canvas.xUnitPerPix);
    }

    /**
    *   @brief  Gives the y-coordinate that the given value should be placed at
    *
    *   @param  yval    The y-value to determine the y-coordinate of
    *
    *   @return The y-coordinate that the given y-value should be drawn at
    */
    function getYPixel(yval) {
        return Math.round((yval - canvas.minY) / canvas.yUnitPerPix);
    }

    /**
    *   @brief Used to convert milliseconds from the beginning of recording to a suitable
    *           text representation of the elapsed time.
    *
    *   @param milli The number of milliseconds from the beginning of recording
    *
    *   @return A text representation of the elapsed time
    */
    function milliToTime(milli) {
        var seconds = (Math.round(milli / 1000) % 60);

        if(seconds < 10)
            seconds = "0" + seconds.toString();
        else
            seconds = seconds.toString();

        var minutes = Math.floor(milli / 1000 / 60) % 60;

        if(minutes < 10)
            minutes = "0" + minutes.toString();
        else
            minutes = minutes.toString();

        var hours = Math.floor(milli / 1000 / 60 / 60) % 24;
        return hours.toString() + ":" + minutes + ":" + seconds;
    }
}
