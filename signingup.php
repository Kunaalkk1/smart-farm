<?php      
        $host = "localhost";  
        $user = "root";  
        $password = "";  
        $db_name = "login_details";  
          
        $con = mysqli_connect($host, $user, $password, $db_name);  
        if(mysqli_connect_errno()) {  
            die("Failed to connect with MySQL: ". mysqli_connect_error()); 
            echo "Connection Failed"; 
        }    
    $username = $_POST['username'];  
    $password = $_POST['password'];  
      
        //to prevent from mysqli injection  
        $username = stripcslashes($username);  
        $password = stripcslashes($password);  
        $username = mysqli_real_escape_string($con, $username);  
        $password = mysqli_real_escape_string($con, $password);  
        $sql = "insert into login values ('$username','$password')";  
        $result = mysqli_query($con, $sql);  
          
        if($result == 1){  
            echo "<script>
            function myFunction() {
              window.location.replace('login.html')
            }
            </script>
            <br><br><h1 style='text-align:center;'> Sign up Successful.</h1>
            <p style='text-align:center;'><button onclick='myFunction()'>Proceed to login</button></p>";
        }  
        else{  
            echo "<script>
            function myFunction() {
              window.location.replace('signup.html')
            }
            </script><br><br><h1 style='text-align:center;'>Signup failed.</h1>
            <p style='text-align:center;'><button onclick='myFunction()'>Retry</button></p>";  
        } 
?>