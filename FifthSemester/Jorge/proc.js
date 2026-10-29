import  { fork } from 'node:child_process';
import { pid,exit} from 'node:process';
import { Worker,isMainThread,} from 'node:worker_threads';

function dormir(ms){
    return new Promise((resolve)=>{
        setTimeout(resolve, ms);
    });
}

function fibo(n){
  if (n <= 1) {
    return n;
  }
  return fibo(n - 1) + fibo(n - 2);
}

if(process.send){
    const myId=pid;
    console.log(`hola desde el proceso hijo ${myId}`)
    //await dormir(10000)
    //fibo(1000)
    exit()
    console.log("adios desde el proceso hijo");

} else{
    const myId=pid;
    console.log(`hola desde el proceso padre ${myId}`)
    var hijo=fork("proc.js");
    //await dormir(15000)
    //exit()
    fibo(1000)
    console.log("adios desde el proceso padre");
}

/*if(isMainThread){
    const myId=pid;
    console.log(`hola desde el thread padre ${myId}`)
    const worker=new Worker("./proc.js");
    //await dormir(15000)
    //exit()
    //fibo(1000)
    console.log("adios desde el thread padre");
}else{
    const myId=pid;
    console.log(`hola desde el thread hijo ${myId}`)
    //await dormir(10000)
    //fibo(40)
    //exit()
    console.log("adios desde el thread hijo");
}*/

