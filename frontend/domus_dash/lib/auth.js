// lib/auth.js

export async function createUsuario(username, password) {
    console.log(username);
    console.log(password);
    const res = await fetch('http://localhost:8080/api/auth/register', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ username, password }),
  });

 if (!res.ok) {
    const errorText = await res.text(); // para ver o que o backend respondeu
    console.error('Erro ao cadastrar:', errorText);
    throw new Error(`Falha ao cadastrar: ${res.status}`);
  }

  const data = await res.json();
  return data.id; // Assumindo que a API REST retorna { token: "..." }
}

export async function loginUsuario(username, password) {
    const res = await fetch('http://localhost:8080/api/auth/login', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ username, password }),
  });

 if (!res.ok) {
    const errorText = await res.text(); // para ver o que o backend respondeu
    console.error('Erro no login:', errorText);
    throw new Error(`Falha no login: ${res.status}`);
  }

  const data = await res.json();
  return data.token; // Assumindo que a API REST retorna { token: "..." }
}
