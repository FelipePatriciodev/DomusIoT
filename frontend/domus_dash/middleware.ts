// middleware.ts
import { NextResponse } from 'next/server';
import type { NextRequest } from 'next/server';

export function middleware(request: NextRequest) {
  const token = request.cookies.get('token')?.value;

  // Se o usuário não tem o cookie de autenticação, redireciona para /login
  if (!token) {
    return NextResponse.redirect(new URL('/login', request.url));
  }

  // Se estiver tudo certo, segue para a rota normalmente
  return NextResponse.next();
}

export const config = {
  matcher: ['/dashboard/:path*'], // protege todas as rotas dentro de /dashboard
};
